import os
from dotenv import load_dotenv
from ollama import chat

load_dotenv()

NUM_RUNS_TIMES = 5

YOUR_SYSTEM_PROMPT = """
You are a k-shot character transcription assistant.

Task: reverse the provided raw character sequence. This is copying, not
spelling. Never use word meaning, pronunciation, abbreviations, prefixes, or
suffixes.

Algorithm to follow silently:
1. Read the input as numbered lowercase characters from left to right.
2. Write the characters from the largest number down to 1.
3. Remove any spaces between copied characters.
4. Verify the output length and character counts exactly match the input.

For a 10-character input, always use this order:
10 9 8 7 6 5 4 3 2 1

Use an index table mentally. For example, if the input is:
1:a 2:b 3:c 4:d 5:e 6:f 7:g 8:h 9:i 10:j
the output is positions 10,9,8,7,6,5,4,3,2,1:
jihgfedcba

Few-shot examples:
Input characters: a b c
Output: cba

Input characters: a b c d e f g h i j
Output: jihgfedcba

Input characters: r e d b l u e
Output: eulbder

Input characters: a p i c l i e n t
Output: tneilcipa

Input characters: h t t p e r r o r
Output: rorreptth

Input characters: w e b s t a t u s
Output: sutatsbew

Input characters: s t a t u s
Output: sutats

Input characters: p i n g s t a t u s
Output: sutatsgnip

Input characters: p o r t s t a t u s
Output: sutatstrop

Critical checks:
- The sequence s t a t u s reverses to s u t a t s. Outputs like staus,
  status, statuts, tatus, or tusats are copying errors.
- If an input begins h t t p, the reversed output ends p t t h.
- For any 10 input characters, the output must have exactly 10 characters.

Return only the final lowercase string. No spaces, punctuation, quotes, code
block, capitalization, or explanation.
"""

USER_PROMPT = """
Reverse this raw character sequence. Only output the reversed string, no other text.

Input characters: h t t p s t a t u s
"""


EXPECTED_OUTPUT = "sutatsptth"

def test_your_prompt(system_prompt: str) -> bool:
    """Run the prompt up to NUM_RUNS_TIMES and return True if any output matches EXPECTED_OUTPUT.

    Prints "SUCCESS" when a match is found.
    """
    for idx in range(NUM_RUNS_TIMES):
        print(f"Running test {idx + 1} of {NUM_RUNS_TIMES}")
        response = chat(
            model="mistral-nemo:12b",
            messages=[
                {"role": "system", "content": system_prompt},
                {"role": "user", "content": USER_PROMPT},
            ],
            options={"temperature": 0.5},
        )
        output_text = response.message.content.strip()
        if output_text.strip() == EXPECTED_OUTPUT.strip():
            print("SUCCESS")
            return True
        else:
            print(f"Expected output: {EXPECTED_OUTPUT}")
            print(f"Actual output: {output_text}")
    return False

if __name__ == "__main__":
    test_your_prompt(YOUR_SYSTEM_PROMPT)
