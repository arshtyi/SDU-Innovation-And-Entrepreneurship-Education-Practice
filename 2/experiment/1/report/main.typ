#import "@preview/numbly:0.1.0": numbly
#import "@preview/pointless-size:0.1.2": zh, zihao
#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.10": *

#let fonts = (main: "Source Han Serif SC", mono: "JetBrains Mono", cjk: "Noto Serif CJK SC")
#let institute = "计算机科学与技术"
#let course = "创新创业教育实践实践"
#let author = "arshtyi"
#let id = "821600046"
#let class = "xxx"
#let date = datetime.today()
#let title = "Prompting Techniques"

#set document(title: title, author: author, date: date)
#set text(font: (fonts.main, fonts.cjk), size: zh(5), lang: "zh", region: "cn")
#set par(justify: true, first-line-indent: (amount: 2em, all: true))
#set page(
    paper: "a4",
    margin: (x: 35pt, y: 35pt),
    footer: align(center, context counter(page).display("- 1 -")),
)
#set heading(numbering: numbly("", "{2:1}.", "({3:1})"))
#show heading: set text(size: zh(-4))
#{
    set underline(offset: 2.5pt, extent: 2.5pt)
    show heading: it => align(center, text(tracking: .1em, size: zh(-2), it))
    heading(numbering: none, level: 1)[山东大学 #underline[#institute] 学院\ #underline[#course] 课程实验报告]
    set text(size: zh(-4))
    set table.cell(inset: .5em, align: left + horizon, stroke: 1pt)
    table(
        columns: (3fr, 1fr),
        [题目：#title], [学号：#id],
    )
    v(0em, weak: true)
    table(
        columns: (1.5fr,) + (1fr,) * 2,
        [日期：#date.display("[year].[month].[day]")], [班级：#class], [姓名：#author],
    )
}
#show raw: set text(font: (fonts.mono, fonts.cjk))
#show raw.where(block: false): box.with(
    fill: luma(240),
    inset: (x: 0.3em, y: 0em),
    outset: (x: 0em, y: 0.3em),
    radius: 0.2em,
)
#show: codly-init
#codly(
    languages: codly-languages,
    zebra-fill: none,
    fill: luma(248),
    stroke: 0.5pt + rgb("bfbfbf"),
    radius: 4pt,
)
#set enum(numbering: numbly("{1:1})", "{2:a}."))
#set list(indent: 6pt, marker: sym.bullet.tri)

#let in-block(body) = {
    let is-level-1-heading(it) = (
        it.func() == heading
            and (
                it.at("level", default: none) == 1
                    or (it.at("offset", default: none) + it.at("depth", default: none) == 1)
            )
    )

    let text-block(it) = {
        v(0em, weak: true)
        block(
            width: 100%,
            inset: (x: 4pt, y: 1em),
            stroke: 1pt,
            breakable: true,
            it,
        )
    }

    let children = body.at("children", default: (body,))
    let content = ()
    let buf = ()

    for child in children {
        if is-level-1-heading(child) {
            if buf.len() > 0 {
                content.push(text-block(buf.join()))
                buf = ()
            }
            buf.push(child)
        } else if buf.len() > 0 {
            buf.push(child)
        } else {
            content.push(child)
        }
    }
    if buf.len() > 0 {
        content.push(text-block(buf.join()))
    }
    content.join()
}
#show: in-block
#let ok = box(
    fill: rgb("e8f5e9"),
    stroke: 0.5pt + rgb("7cb383"),
    radius: 3pt,
    inset: (x: 5pt, y: 2pt),
    text(fill: rgb("1b5e20"), weight: "bold")[SUCCESS],
)

= 实验目的

本实验对应 CS146S Week 1 的 Prompting Techniques 练习。实验目标是在不修改模型与评测逻辑的前提下，为六类提示工程方法补全提示词，使本地大语言模型能够通过对应脚本中的自动检查。六类方法分别为 K-shot prompting、Chain-of-thought、Tool calling、Self-consistency prompting、RAG 和 Reflexion。

= 实验环境

#table(
    columns: (1.1fr, 3fr),
    align: (left, left),
    [项目], [配置],
    [操作系统], [WSL Ubuntu 24.04],
    [Python], [`3.11`],
    [依赖], [`ollama 0.6.2`、`python-dotenv 1.2.2`],
    [本地模型], [`mistral-nemo:12b` 用于 K-shot；`llama3.1:8b` 用于其余任务],
)

```bash
uv sync
uv run prompt_engineering/chain_of_thought.py > output/chain_of_thought.txt && \
    uv run prompt_engineering/k_shot_prompting.py > output/k_shot_prompting.txt && \
    uv run prompt_engineering/rag.py > output/rag.txt && \
    uv run prompt_engineering/reflexion.py > output/reflexion.txt && \
    uv run prompt_engineering/self_consistency_prompting.py > output/self_consistency_prompting.txt && \
    uv run prompt_engineering/tool_calling.py > output/tool_calling.txt
```

= 实验步骤

#table(
    columns: (1.2fr, 1.1fr, 1.35fr, 0.7fr),
    align: (left, left, left, center),
    [任务], [模型], [源文件], [结果],
    [K-shot prompting], [`mistral-nemo:12b`], [`k_shot_prompting.py`], ok,
    [Chain-of-thought], [`llama3.1:8b`], [`chain_of_thought.py`], ok,
    [Tool calling], [`llama3.1:8b`], [`tool_calling.py`], ok,
    [Self-consistency], [`llama3.1:8b`], [`self_consistency_prompting.py`], ok,
    [RAG], [`llama3.1:8b`], [`rag.py`], ok,
    [Reflexion], [`llama3.1:8b`], [`reflexion.py`], ok,
)

== K-shot prompting

该任务要求把给定字符串逐字符反转。强调"字符转录"而非"单词理解"，并使用相似但不相同的样例约束 `status` 片段的反转方式。

```text
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
```

output：

```text
Running test 1 of 5
SUCCESS
```

== Chain-of-thought

该任务计算 `3^12345 (mod 100)`。为了减少现场计算错误，提示词给出 `3^n mod 100` 的完整 20 项循环表，再让模型进行指数取模和查表；同时保留奇指数下模 4 的校验。

```text
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
```

output：

```text
Running test 1 of 5
SUCCESS
```

== Tool calling

该任务要求模型不要直接回答，而是输出可解析的 JSON 工具调用。工具执行后会读取当前 Python 文件中每个顶层函数的返回类型。

```text
You are a strict tool-routing assistant.
You do not execute tools or answer the tool result yourself. Your only job is to
emit the JSON object for the tool call that should be executed.

Available tool:

output_every_func_return_type(file_path: str = "") -> str
  Returns the top-level Python function names and their return annotations for
  the requested file. If the user asks for the current file or gives no file
  path, pass an empty string for file_path.

Decision rules:
- When the user asks to call, run, or use the available tool, choose
  output_every_func_return_type.
- Include exactly the arguments required by the tool.
- Output exactly one valid JSON object and nothing else.
- Use double quotes for every JSON key and string value.
- Do not use Markdown, prose, comments, code fences, trailing commas, or extra
  keys.

Required schema:
{"tool": "output_every_func_return_type", "args": {"file_path": ""}}
```

output：

```text
{'tool': 'output_every_func_return_type', 'args': {'file_path': ''}}
Generated tool call: {'tool': 'output_every_func_return_type', 'args': {'file_path': '/mnt/d/camp/bachelor/course/innovationandentrepreneurshipeducationpractice/2/experiment/1/prompt_engineering/tool_calling.py'}}
Generated output: _annotation_to_str: str
_list_function_return_types: List[Tuple[str, str]]
add: int
compute_expected_output: str
execute_tool_call: str
extract_tool_call: Dict[str, Any]
greet: str
output_every_func_return_type: str
resolve_path: str
run_model_for_tool_call: Dict[str, Any]
test_your_prompt: bool
SUCCESS
```

== Self-consistency prompting

该任务是路程应用题。提示词要求模型静默使用至少两种等价设定：一是把停车点转换成从起点算起的里程标记，二是检查三段路程之和是否等于总路程。脚本以五次运行的多数结果作为判定。

```text
You are a precise self-consistency solver for arithmetic word problems.
Do all reasoning silently, using at least two equivalent setups before deciding
on the final answer.

For trip and stop problems:
- Convert each stop description into a mile marker measured from the start.
- A stop described as r miles before the end of a trip of length t is at marker
  t - r.
- The distance between two stops is later_marker - earlier_marker.
- Independently check the segment equation:
  distance_before_first_stop + distance_between_stops + distance_after_second_stop
  = total_trip_length.
- If the two setups disagree, recompute from the mile markers.

Return only the final answer in exactly this one-line format:
Answer: <number>
```

output：

```text
Running test 1 of 5
Run 1 answer: Answer: 25
Running test 2 of 5
Run 2 answer: Answer: 25
Running test 3 of 5
Run 3 answer: Answer: 25
Running test 4 of 5
Run 4 answer: Answer: 25
Running test 5 of 5
Run 5 answer: Answer: 25
Majority answer: Answer: 25 (5/5)
SUCCESS
```

== RAG

该任务要求根据检索到的 API 文档生成一个 Python 函数。提示词明确 API 事实只能来自上下文；上下文提供器使用关键词打分选择包含 base URL、鉴权头和 `/users/{id}` 端点的文档。

```text
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
```

output：

````text
Running test 1 of 5
```python
import requests

def fetch_user_name(user_id: str, api_key: str) -> str:
    base_url = "https://api.example.com/v1"
    endpoint = f"/users/{user_id}"
    url = f"{base_url}{endpoint}"

    headers = {"X-API-Key": api_key}
    response = requests.get(url, headers=headers)

    response.raise_for_status()
    data = response.json()
    return data["name"]
```
SUCCESS
````

== Reflexion

该任务先让模型生成初始密码校验函数，再把失败样例和诊断反馈给模型进行一次自我修正。最终提示强调保留已有正确规则，并把大小写、数字和 special symbol 拆成独立谓词。

Reflexion 阶段的系统提示词如下。

```text
You are a reflexion coding assistant for Python validators.
You will receive a previous implementation plus failing test diagnostics. Use
the diagnostics to infer which predicates are missing or too broad, preserve
checks that still make sense, and return a corrected implementation.

Guidelines:
- Keep the required function name and signature exactly: is_valid_password(password: str) -> bool.
- Represent password character classes as separate checks: lowercase,
  uppercase, digit, and special symbol when those requirements are present or
  implied.
- Treat "special" as membership in this symbol set only: !@#$%^&*()-_
  Letters, digits, and ordinary whitespace do not satisfy the special-symbol
  requirement.
- A valid password should satisfy every inferred rule at the same time using
  logical AND.
- Return only one fenced Python code block.
- Do not include prose, comments, tests, imports, or extra code outside the function.
```

Reflexion 阶段的用户提示词如下。

````text
Previous implementation:
```python
def is_valid_password(password: str) -> bool:
    return len(password) >= 8 and any(c.islower() for c in password) and any(c.isdigit() for c in password)
```

Failing tests and diagnostics:
- Input: password1! → expected False, got True. Failing checks: missing uppercase
- Input: Password1 → expected False, got True. Failing checks: missing special

Reflect on the failed cases and repair the validator generally, not just for
the listed example strings.

Requirements for the revision:
- Keep the exact function signature.
- Preserve useful existing checks such as minimum length and digit checks unless
  the diagnostics contradict them.
- Replace broad alphabetic checks with explicit lowercase and uppercase checks
  when case-specific diagnostics appear.
- Check special symbols by membership in !@#$%^&*()-_, not by testing for
  "not lowercase", "not alphabetic", or "not alphanumeric".
- Return True only if all required predicates pass.

Return only the corrected fenced Python code block.
````

output：

````text
Initial code:
def is_valid_password(password: str) -> bool:
    return len(password) >= 8 and any(c.islower() for c in password) and any(c.isdigit() for c in password)
FAILURE (initial implementation failed some tests): ['Input: password1! → expected False, got True. Failing checks: missing uppercase', 'Input: Password1 → expected False, got True. Failing checks: missing special']
REFLECTION CONTEXT: Previous implementation:
```python
def is_valid_password(password: str) -> bool:
    return len(password) >= 8 and any(c.islower() for c in password) and any(c.isdigit() for c in password)
```

Failing tests and diagnostics:
- Input: password1! → expected False, got True. Failing checks: missing uppercase
- Input: Password1 → expected False, got True. Failing checks: missing special

Reflect on the failed cases and repair the validator generally, not just for
the listed example strings.

Requirements for the revision:
- Keep the exact function signature.
- Preserve useful existing checks such as minimum length and digit checks unless
  the diagnostics contradict them.
- Replace broad alphabetic checks with explicit lowercase and uppercase checks
  when case-specific diagnostics appear.
- Check special symbols by membership in !@#$%^&*()-_, not by testing for
  "not lowercase", "not alphabetic", or "not alphanumeric".
- Return True only if all required predicates pass.

Return only the corrected fenced Python code block.,
You are a reflexion coding assistant for Python validators.
You will receive a previous implementation plus failing test diagnostics. Use
the diagnostics to infer which predicates are missing or too broad, preserve
checks that still make sense, and return a corrected implementation.

Guidelines:
- Keep the required function name and signature exactly: is_valid_password(password: str) -> bool.
- Represent password character classes as separate checks: lowercase,
  uppercase, digit, and special symbol when those requirements are present or
  implied.
- Treat "special" as membership in this symbol set only: !@#$%^&*()-_
  Letters, digits, and ordinary whitespace do not satisfy the special-symbol
  requirement.
- A valid password should satisfy every inferred rule at the same time using
  logical AND.
- Return only one fenced Python code block.
- Do not include prose, comments, tests, imports, or extra code outside the function.


Improved code:
def is_valid_password(password: str) -> bool:
    special_symbols = "!@#$%^&*()-_"
    return len(password) >= 8 and any(c.islower() for c in password) and any(c.isupper() for c in password) and any(c.isdigit() for c in password) and any(s in password for s in special_symbols)
SUCCESS
````

= 实验总结

本次实验的核心不是调整模型参数，而是在固定模型和固定评测逻辑下，通过提示词约束模型的行为。

K-shot 任务说明，对于看似简单的字符串反转，模型仍可能按语义块进行加工；将输入改写为带空格的原始字符序列，并提供相似片段的正反例，可以显著降低错误。Chain-of-thought 任务说明，开放式推理容易在中间算术上出错；把可复用的数学结构显式化为查表规则后，结果更稳定。Tool calling 的关键是输出格式约束，必须让模型只产生 JSON，不产生解释文本。Self-consistency 通过多路径静默校验提高了应用题稳定性。RAG 的重点是把 API 事实绑定到检索上下文，避免模型编造接口细节。Reflexion 则体现了"失败诊断 -> 修正规则 -> 重新生成"的迭代流程，尤其适合从测试失败中补齐遗漏条件。
