import os
import re
from typing import List, Callable
from dotenv import load_dotenv
from ollama import chat

load_dotenv()

NUM_RUNS_TIMES = 5

DATA_FILES: List[str] = [
    os.path.join(os.path.dirname(__file__), "data", "api_docs.txt"),
]


def load_corpus_from_files(paths: List[str]) -> List[str]:
    corpus: List[str] = []
    for p in paths:
        if os.path.exists(p):
            try:
                with open(p, "r", encoding="utf-8") as f:
                    corpus.append(f.read())
            except Exception as exc:
                corpus.append(f"[load_error] {p}: {exc}")
        else:
            corpus.append(f"[missing_file] {p}")
    return corpus


# Load corpus from external files (simple API docs). If missing, fall back to inline snippet
CORPUS: List[str] = load_corpus_from_files(DATA_FILES)

QUESTION = (
    "Write a Python function `fetch_user_name(user_id: str, api_key: str) -> str` that calls the documented API "
    "to fetch a user by id and returns only the user's name as a string."
)


YOUR_SYSTEM_PROMPT = """
You are a retrieval-grounded Python coding assistant.
Treat the supplied context as the source of truth for API facts: base URL,
endpoint paths, authentication headers, parameters, and response fields. Do not
invent or substitute API details from memory.

Return exactly one fenced Python code block and no prose. The code must:
- import any needed library
- define the requested function with the requested signature
- build the request URL from the documented base URL and endpoint
- call requests.get with the documented authentication header
- call raise_for_status() before using the response body
- parse the JSON response
- return only the requested field as the requested Python type
"""


# For this simple example
# For this coding task, validate by required snippets rather than exact string
REQUIRED_SNIPPETS = [
    "def fetch_user_name(",
    "requests.get",
    "/users/",
    "X-API-Key",
    "return",
]


def YOUR_CONTEXT_PROVIDER(corpus: List[str]) -> List[str]:
    """Select and return the relevant subset of documents from CORPUS for this task.

    For example, return [] to simulate missing context, or [corpus[0]] to include the API docs.
    """
    query_terms = [
        "api",
        "base url",
        "authentication",
        "header",
        "user",
        "users",
        "name",
        "get",
    ]
    scored_docs: list[tuple[int, int, str]] = []
    for idx, doc in enumerate(corpus):
        normalized = doc.lower()
        score = sum(1 for term in query_terms if term in normalized)
        if "x-api-key" in normalized:
            score += 2
        if "get /users" in normalized or "/users/" in normalized:
            score += 3
        if "base url" in normalized:
            score += 2
        if score > 0:
            scored_docs.append((score, idx, doc))

    scored_docs.sort(key=lambda item: (-item[0], item[1]))
    return [doc for _, _, doc in scored_docs[:3]]


def make_user_prompt(question: str, context_docs: List[str]) -> str:
    if context_docs:
        context_block = "\n".join(f"- {d}" for d in context_docs)
    else:
        context_block = "(no context provided)"
    return (
        f"Context (use ONLY this information):\n{context_block}\n\n"
        f"Task: {question}\n\n"
        "Requirements:\n"
        "- Use the documented Base URL and endpoint.\n"
        "- Send the documented authentication header.\n"
        "- Raise for non-200 responses.\n"
        "- Return only the user's name string.\n\n"
        "Output: A single fenced Python code block with the function and necessary imports.\n"
    )


def extract_code_block(text: str) -> str:
    """Extract the last fenced Python code block, or any fenced code block, else return text."""
    # Try ```python ... ``` first
    m = re.findall(r"```python\n([\s\S]*?)```", text, flags=re.IGNORECASE)
    if m:
        return m[-1].strip()
    # Fallback to any fenced code block
    m = re.findall(r"```\n([\s\S]*?)```", text)
    if m:
        return m[-1].strip()
    return text.strip()


def test_your_prompt(system_prompt: str, context_provider: Callable[[List[str]], List[str]]) -> bool:
    """Run up to NUM_RUNS_TIMES and return True if any output matches EXPECTED_OUTPUT."""
    context_docs = context_provider(CORPUS)
    user_prompt = make_user_prompt(QUESTION, context_docs)

    for idx in range(NUM_RUNS_TIMES):
        print(f"Running test {idx + 1} of {NUM_RUNS_TIMES}")
        response = chat(
            model="llama3.1:8b",
            messages=[
                {"role": "system", "content": system_prompt},
                {"role": "user", "content": user_prompt},
            ],
            options={"temperature": 0.0},
        )
        output_text = response.message.content
        code = extract_code_block(output_text)
        missing = [s for s in REQUIRED_SNIPPETS if s not in code]
        if not missing:
            print(output_text)
            print("SUCCESS")
            return True
        else:
            print("Missing required snippets:")
            for s in missing:
                print(f"  - {s}")
            print("Generated code:\n" + code)
    return False


if __name__ == "__main__":
    test_your_prompt(YOUR_SYSTEM_PROMPT, YOUR_CONTEXT_PROVIDER)
