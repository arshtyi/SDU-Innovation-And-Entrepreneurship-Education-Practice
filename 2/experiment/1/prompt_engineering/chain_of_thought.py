import os
import re
from dotenv import load_dotenv
from ollama import chat

load_dotenv()

NUM_RUNS_TIMES = 5

YOUR_SYSTEM_PROMPT = """
You are a careful modular-arithmetic tutor.

For powers of 3 modulo 100, use the full repeated-multiplication cycle below.
The cycle length is 20, so reduce the exponent modulo 20. A remainder of 0
means use the row labeled 20.

remainder n mod 20 -> 3^n mod 100
1 -> 3
2 -> 9
3 -> 27
4 -> 81
5 -> 43
6 -> 29
7 -> 87
8 -> 61
9 -> 83
10 -> 49
11 -> 47
12 -> 41
13 -> 23
14 -> 69
15 -> 7
16 -> 21
17 -> 63
18 -> 89
19 -> 67
20 or 0 -> 1

Use the table as a deterministic lookup after reducing the exponent. Do not
answer with the exponent remainder, a modulo-25 residue, or an unverified CRT
candidate.

As a check, for an odd exponent the final residue must be congruent to 3 modulo
4, because 3^odd = 3 (mod 4).

Show concise step-by-step reasoning for the user's exponent, then end with
exactly one final line in this format:
Answer: <number>
"""


USER_PROMPT = """
Solve this problem, then give the final answer on the last line as "Answer: <number>".

what is 3^{12345} (mod 100)?
"""


# For this simple example, we expect the final numeric answer only
EXPECTED_OUTPUT = "Answer: 43"


def extract_final_answer(text: str) -> str:
    """Extract the final 'Answer: ...' line from a verbose reasoning trace.

    - Finds the LAST line that starts with 'Answer:' (case-insensitive)
    - Normalizes to 'Answer: <number>' when a number is present
    - Falls back to returning the matched content if no number is detected
    """
    matches = re.findall(r"(?mi)^\s*answer\s*:\s*(.+)\s*$", text)
    if matches:
        value = matches[-1].strip()
        # Prefer a numeric normalization when possible (supports integers/decimals)
        num_match = re.search(r"-?\d+(?:\.\d+)?", value.replace(",", ""))
        if num_match:
            return f"Answer: {num_match.group(0)}"
        return f"Answer: {value}"
    return text.strip()


def test_your_prompt(system_prompt: str) -> bool:
    """Run up to NUM_RUNS_TIMES and return True if any output matches EXPECTED_OUTPUT.

    Prints "SUCCESS" when a match is found.
    """
    for idx in range(NUM_RUNS_TIMES):
        print(f"Running test {idx + 1} of {NUM_RUNS_TIMES}")
        response = chat(
            model="llama3.1:8b",
            messages=[
                {"role": "system", "content": system_prompt},
                {"role": "user", "content": USER_PROMPT},
            ],
            options={"temperature": 0.3},
        )
        output_text = response.message.content
        final_answer = extract_final_answer(output_text)
        if final_answer.strip() == EXPECTED_OUTPUT.strip():
            print("SUCCESS")
            return True
        else:
            print(f"Expected output: {EXPECTED_OUTPUT}")
            print(f"Actual output: {final_answer}")
    return False


if __name__ == "__main__":
    test_your_prompt(YOUR_SYSTEM_PROMPT)
