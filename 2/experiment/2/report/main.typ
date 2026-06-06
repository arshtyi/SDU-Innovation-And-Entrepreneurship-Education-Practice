#import "@preview/numbly:0.1.0": numbly
#import "@preview/pointless-size:0.1.2": zh, zihao
#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.10": *

#let fonts = (main: "Noto Serif CJK SC", mono: "JetBrains Mono", cjk: "Noto Serif CJK SC")
#let institute = "计算机科学与技术"
#let course = "创新创业教育实践实践"
#let author = "arshtyi"
#let id = "202400130242"
#let class = "24智能"
#let date = datetime.today()
#let title = "Model Context Protocol"

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
#set raw(syntaxes: "highlight/PowerShell.sublime-syntax")
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

本实验围绕 Model Context Protocol（MCP）完成一个可在本地运行、可被 Codex 调用的工具服务器。实验目标包括：理解 MCP server 通过标准输入输出与客户端通信的基本方式；使用 `FastMCP` 声明工具并暴露给 AI 助手；将第三方游戏王卡片查询能力封装为 MCP 工具；完成本地协议冒烟测试，并把该 server 注册到 Codex 的 MCP 配置中进行实际调用。

= 实验环境

#table(
    columns: (1.1fr, 3fr),
    align: (left, left),
    [项目], [配置],
    [操作系统], [Windows 11],
    [Python], [3.14.5],
    [uv], [0.11.19],
    [依赖], [mcp: 1.27.2, ygoutil: 0.2.2],
    [MCP 客户端], [Codex CLI],
    [数据], [ygoutil.source.BaiGe，通过 #link("ygocdb.com") 查询卡片信息],
)

项目使用 `pyproject.toml` 和 `uv.lock` 管理依赖。

```toml
[project]
name = "2"
version = "0.1.0"
requires-python = ">=3.12"
dependencies = ["mcp[cli]>=1.27.2", "ygoutil>=0.2.2"]
```

= 实验步骤

== MCP Server 实现

本实验的 MCP server 位于 `src/ygo/server.py`。代码创建了名为 `ygo_card_baige` 的 `FastMCP` 实例，并注册 `query_ygo_card` 工具。工具参数为用户输入的卡片查询字符串，返回值为卡片信息字符串；若查询不到结果则返回 `None`。

```python
from mcp.server.fastmcp import FastMCP
from ygoutil.source import BaiGe
mcp = FastMCP("ygo_card_baige")
@mcp.tool()
async def query_ygo_card(query: str) -> str | None:
    """
    通过 query 查询，得到一张游戏王卡的信息
    """
    source = BaiGe()
    card = await source.from_query(query)
    if card is None:
        return None
    return card.info()
if __name__ == "__main__":
    mcp.run()
```

该 server 没有显式开启 HTTP 服务，而是采用 `mcp.run()` 的默认 stdio transport。也就是说，本地直接运行该命令后进程会等待 MCP 客户端通过标准输入发送 JSON-RPC 请求，客户端再从标准输出读取响应。

== 本地启动

在项目目录下运行以下命令即可启动 MCP server：

```powershell
cd D:\campus\bachelor\course\innovationandentrepreneurshipeducationpractice\2\experiment\2
uv run src/ygo/server.py
```

该命令不会像 Web 服务一样输出访问端口；它会阻塞等待客户端连接，这是 stdio MCP server 的正常状态。

== 协议冒烟测试

为了验证 server 是否正确暴露工具，可以向进程写入 MCP JSON-RPC 请求，依次执行 `initialize`、`notifications/initialized` 和 `tools/list`。测试结果显示服务端名称为 `ygo_card_baige`，并成功返回一个工具 `query_ygo_card`。

```json
{
  "serverInfo": {
    "name": "ygo_card_baige",
    "version": "1.27.2"
  },
  "tools": [
    {
      "name": "query_ygo_card",
      "description": "通过 query 查询，得到一张游戏王卡的信息",
      "inputSchema": {
        "properties": {
          "query": {
            "type": "string"
          }
        },
        "required": ["query"]
      }
    }
  ]
}
```

随后直接调用工具函数查询 `青眼白龙`，能够返回卡片中文名、日文名、英文名、类型、密码、种族属性、星级、攻守数值和效果描述，说明业务逻辑和外部数据源也可以正常工作。

```text
青眼白龙
青眼の白龍
Blue-Eyes White Dragon
通常 怪兽
89631139
龙族  光属性  8星
3000 / 2500
以高攻击力著称的传说之龙。任何对手都能粉碎，其破坏力不可估量。
```

== 接入 Codex

由于该 server 使用 stdio transport，接入 Codex 时需要把启动命令注册到 Codex 的 MCP 配置中，由 Codex 在需要时自动拉起该进程：

```powershell
codex mcp add ygo_card_baige -- uv --directory "D:\campus\bachelor\course\innovationandentrepreneurshipeducationpractice\2\experiment\2" run src/ygo/server.py
Added global MCP server 'ygo_card_baige'.
```

注册后使用 `codex mcp list` 检查状态：

```powershell
codex mcp list
Name            Command  Args                                                                                                                              Env  Cwd  Status   Auth
ygo_card_baige  uv       --directory D:\campus\bachelor\course\innovationandentrepreneurshipeducationpractice\2\experiment\2 run python src/ygo/server.py  -    -    enabled  Unsupported
```

在 Codex 中输入"用 ygo_card_baige \"看透心灵之眼\""后，客户端会发现该 MCP 工具并调用 `query_ygo_card`，返回的结果如下图所示。

#figure(
    image("fig/test.png"),
    caption: [Codex 调用 `query_ygo_card` 查询卡片信息],
)

= 实验总结

本次实验完成了一个从实现到本地接入的 MCP server。实现层面上，`FastMCP` 将 Python 异步函数包装为 MCP 工具，开发者只需要定义函数签名、文档字符串和返回值即可让客户端获得工具名称、描述与参数 schema。运行层面上，stdio MCP server 不需要常驻端口，而是由客户端按配置启动进程并通过 JSON-RPC 交换消息。
