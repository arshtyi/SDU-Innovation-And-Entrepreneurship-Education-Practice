#import "@preview/numbly:0.1.0": numbly
#import "@preview/pointless-size:0.1.2": zh, zihao
#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.10": *

#let fonts = (main: "Noto Serif CJK SC", mono: "JetBrains Mono", cjk: "Noto Serif CJK SC")
#let institute = "计算机科学与技术"
#let course = "创新创业教育实践"
#let author = "彭靖轩"
#let id = "202400130242"
#let class = "24智能"
#let date = datetime.today()
#let title = "课程作业提交管理小工具"

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

#let file-block(path, lang: "text") = {
    raw(read(path), lang: lang, block: true)
}

= 实验目的

本次实验围绕"课程作业提交管理小工具"这一统一题目，完成了一次从需求表达、AI 辅助生成、运行验证、问题迭代、结构化 Code Review 到审查后修复的完整开发闭环。实验的重点不是追求复杂功能，而是验证在受控范围内使用 AI 生成项目、审查项目并由人工做最终判断的工程流程。

本实验需要达成的目标包括：

+ 使用 AI 根据结构化 Prompt 生成一个可运行的小型前端项目。
+ 验证生成结果是否满足课程作业管理的核心需求。
+ 在运行和界面检查中发现问题，并通过最小修改完成迭代。
+ 发起结构化代码审查，区分必须修改的问题和建议优化的问题。
+ 对 AI 审查结果进行人工筛选，并补充 AI 未充分覆盖的问题。
+ 根据审查结果完成最终修复并重新验证。

= 实验环境

== 基本信息

#table(
    columns: (1.2fr, 3fr),
    inset: 6pt,
    stroke: 0.5pt,
    [姓名], [彭靖轩],
    [学号], [202400130242],
    [班级], [24智能],
    [使用模型], [GPT5.5],
    [项目类型], [无后端 Web 单页应用],
    [技术栈], [React、TypeScript、Vite、纯 CSS、localStorage],
)

环境测试已完成，记录见 `note/1/main.md`。测试截图如下：

#image("../note/1/fig/1.png", width: 70%)

== 项目目录

本实验按手册建议将材料拆分为项目代码、过程记录、Prompt、代码审查记录和实验报告：

+ `project/`：React + TypeScript + Vite 项目源码。
+ `note/`：阶段性实验记录，包括环境、Prompt 设计、生成运行、迭代和审查筛选。
+ `prompt/`：初始项目生成、UI 修复、Code Review、基于 Review 修复的 Prompt。
+ `review/`：人工筛选后的审查记录。
+ `report/`：本实验报告。

= 实验步骤

== 阶段一：环境检查与实验准备

实验开始前确认了 AI 工具和模型可用性，并完成了基础环境测试。记录中使用的模型为 GPT5.5，环境测试结果为通过。由于项目使用 Vite 前端工具链，因此还确认了本机具备 Node.js、npm 和浏览器运行能力。

== 阶段二：Prompt 设计

初始 Prompt 没有采用"帮我做一个作业管理系统"这类模糊表达，而是明确约束了角色、项目名称、技术栈、核心功能、扩展功能、页面设计、数据结构、文件结构和输出顺序。这样做的目的是降低 AI 过度设计或偏离技术栈的概率。

本次 Prompt 的关键约束如下：

+ 技术栈限定为 React + TypeScript + Vite。
+ 不使用后端数据库，不引入 Redux 或复杂 UI 框架。
+ 使用 `localStorage` 完成页面刷新后的数据保留。
+ 明确要求组件拆分、类型定义和项目根目录。
+ 要求先给开发计划，再创建项目文件，最后说明启动和测试方式。

除基础功能外，Prompt 中加入了搜索、按截止日期排序、优先级、临近截止提醒、逾期高亮、空状态和基础表单校验等扩展功能。完整初始 Prompt 通过外部文件读取如下：

#file-block("../prompt/project.md", lang: "markdown")

== 阶段三：生成初始项目

AI 给出的方案判断为可行：项目是纯前端 SPA，不需要后端；状态使用 React `useState` 管理，筛选结果通过 `useMemo` 派生；持久化通过 `src/utils/storage.ts` 封装；日期判断集中在 `src/utils/date.ts`。

最终项目结构如下：

#file-block("../note/3/list.txt", lang: "txt")

生成后执行：

```powershell
npm install
npm run dev
```

项目可通过 `http://127.0.0.1:5173` 打开，首次运行成功。随后又执行过生产构建检查，`npm run build` 可以通过。

== 阶段四：运行验证与界面迭代

运行验证阶段重点检查了手册中的功能清单：

+ 可以新增作业，并填写课程名、作业标题、截止日期、完成状态和优先级。
+ 可以切换完成状态。
+ 可以删除作业。
+ 可以按课程筛选。
+ 可以按全部、未完成、已完成筛选。
+ 可以搜索课程名或作业标题。
+ 可以按截止日期排序。
+ 页面刷新后数据仍然保留。
+ 临近截止、逾期高亮、高优先级视觉区分和空状态提示能够显示。

在界面检查中发现一个具体问题：筛选区域中排序下拉框的文本发生截断。随后使用最小修改 Prompt 要求 AI 只修复该 UI 问题，不重写项目。

#file-block("../prompt/fix.md", lang: "text")

修复后，排序控件获得更合理的列宽和响应式布局。该问题的记录见 `note/4/main.md`：

#file-block("../note/4/main.md", lang: "markdown")

== 阶段五：AI 辅助代码审查与人工筛选

项目基本可运行后，发起了一次结构化 Code Review。审查 Prompt 明确要求从逻辑与正确性、可读性与可维护性、性能、安全性、工程最佳实践五个维度检查，并要求区分 `[Must]` 与 `[Suggestion]`。

#file-block("../prompt/review.md", lang: "markdown")

审查后，AI 发现的主要问题包括：

+ `localStorage` 读写缺少异常处理。
+ 持久化数据中的日期字段校验不足。
+ 删除课程最后一条作业后，课程筛选状态可能残留。
+ 项目缺少自动化测试。

我对这些意见进行了人工筛选。前三项会影响稳定性或状态一致性，具有修改价值；测试补充是合理建议，但本次按照"完成手册最小闭环"的目标暂不作为当前必须修复项。人工额外补充的问题是：删除操作没有确认、撤销或软删除机制，误删后没有恢复路径，因此至少需要增加删除确认。

人工筛选结果记录如下：

#file-block("../review/main.md", lang: "markdown")

== 阶段六：根据审查结果修改

基于审查结果，最终修复了四类问题：

#table(
    columns: (1.4fr, 2.5fr, 2fr),
    inset: 6pt,
    stroke: 0.5pt,
    [修复项], [修改位置], [效果],
    [`localStorage` 异常处理],
    [`src/utils/storage.ts`, `src/App.tsx`],
    [读写失败时不再导致页面崩溃，并在保存失败时显示提示。],

    [日期合法性校验], [`src/utils/date.ts`, `src/utils/storage.ts`], [过滤损坏或非法的持久化数据，避免渲染或排序异常。],
    [课程筛选状态回退], [`src/App.tsx`], [当前筛选课程被删除后自动回到"全部课程"。],
    [删除确认], [`src/App.tsx`], [删除前弹出确认，降低误删风险。],
)

基于审查修改的 Prompt 记录如下：

#file-block("../prompt/fix-on-review.md", lang: "text")

最终验证方式包括：

+ 执行 `npm run build`，TypeScript 检查和 Vite 构建均通过。
+ 执行 `npm audit --json`，当前依赖审计结果为 0 个漏洞。
+ 重新检查新增、筛选、搜索、排序、完成状态切换、删除确认和本地持久化流程。

= 项目说明

== 功能概述

最终项目是一个适合大学生日常使用的课程作业提交管理小工具。页面顶部显示项目标题和统计信息，左侧为添加作业表单，右侧为筛选、搜索、排序和作业列表区域。

核心功能包括：

+ 添加课程作业。
+ 设置课程名、作业标题、截止日期、完成状态和优先级。
+ 按课程筛选。
+ 按全部、未完成、已完成筛选。
+ 搜索课程名或作业标题。
+ 按截止日期从近到远或从远到近排序。
+ 标记完成或设为未完成。
+ 删除作业。
+ 使用 `localStorage` 在页面刷新后保留数据。

扩展功能包括：

+ 临近截止提醒：截止日期 3 天内且未完成的作业显示提醒。
+ 逾期任务高亮：截止日期已过且未完成的作业明显标记。
+ 优先级视觉区分：高优先级更醒目。
+ 空状态提示：没有匹配作业时显示友好提示。
+ 基础表单校验：课程名、作业标题、截止日期不能为空。

== 关键源码引用

核心状态、筛选、排序和删除确认逻辑位于 `App.tsx`：

#file-block("../project/src/App.tsx", lang: "tsx")

本地存储读写和数据校验位于 `storage.ts`：

#file-block("../project/src/utils/storage.ts", lang: "ts")

日期解析、日期合法性判断、逾期和临近截止判断位于 `date.ts`：

#file-block("../project/src/utils/date.ts", lang: "ts")

= 实验总结

== AI 最有帮助的地方

AI 最有帮助的地方是把一个结构化需求快速转化为可运行项目。只要 Prompt 中明确了技术栈、功能范围、文件结构和输出顺序，AI 可以较快生成完整的 React + TypeScript 项目，并能在发现 UI 问题后做局部修复。这显著降低了从零搭建项目的时间成本。

== AI 最不可靠的地方

AI 最不可靠的地方是它容易满足"表面可运行"，但遗漏边界条件。例如最初版本能够正常新增、筛选和删除作业，但没有充分处理 `localStorage` 访问失败、持久化数据损坏、筛选状态残留和删除误操作等问题。这些问题在正常演示路径中不一定暴露，但会影响稳定性和用户体验。

== 人类在流程中的价值

人类最重要的价值是定义边界、验证事实和承担最终判断。AI 可以生成代码，也可以给出审查意见，但哪些问题真的影响项目、哪些建议暂时不需要做、哪些风险被 AI 漏掉，都需要人工结合项目目标判断。本实验中，我没有直接接受所有审查意见，而是选择修复影响稳定性和可用性的项目，并人工补充了删除确认问题。

== 收获

通过这次实验，我更清楚地体会到 AI 辅助开发的有效方式不是让 AI 一次性"写完全部"，而是把任务拆成需求、生成、验证、修复、审查、再修复几个阶段。每个阶段都应有清晰输入、明确约束和可验证结果。高质量的软件仍然依赖清晰需求、严格验证、有效审查和人类最终负责的工程判断。
