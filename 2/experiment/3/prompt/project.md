你是一名资深前端工程师，请帮我生成一个适合大学生使用的小型 Web 单页应用。

## 项目名称

课程作业提交管理小工具

## 技术栈要求

* 使用 React + TypeScript
* 使用 Vite 创建前端项目
* 使用纯 CSS 或 CSS Modules，不使用复杂 UI 框架
* 不依赖后端
* 使用 localStorage 持久化数据
* 代码结构清晰，可直接本地运行
* 界面简洁、现代、适合大学生使用

## 核心功能

实现课程作业管理功能，支持：

1. 添加课程作业
2. 设置以下字段：

   * 课程名
   * 作业标题
   * 截止日期
   * 完成状态
   * 优先级：低 / 中 / 高
3. 支持按课程筛选
4. 支持按状态筛选：

   * 全部
   * 未完成
   * 已完成
5. 支持搜索作业标题或课程名
6. 支持按截止日期排序
7. 支持标记已完成 / 未完成
8. 支持删除作业
9. 页面刷新后数据仍然保留

## 扩展功能

1. 临近截止提醒：

   * 距离截止日期 3 天内且未完成的任务显示提醒
2. 逾期任务高亮：

   * 截止日期已过且未完成的任务需要明显标记
3. 优先级视觉区分：

   * 高优先级应更醒目
4. 空状态提示：

   * 没有作业时显示友好的提示文案
5. 基础表单校验：

   * 课程名、作业标题、截止日期不能为空

## 页面设计要求

* 整体布局简洁清晰
* 顶部显示项目标题
* 添加作业区域放在页面上方或左侧
* 筛选、搜索、排序区域应集中展示
* 作业列表使用卡片或表格形式展示
* 移动端也应具备基本可用性
* 不要过度设计，不要使用复杂动画

## 推荐数据结构

使用 TypeScript 定义 Assignment 类型：

```ts
type Priority = "low" | "medium" | "high";

type Assignment = {
  id: string;
  course: string;
  title: string;
  dueDate: string;
  completed: boolean;
  priority: Priority;
  createdAt: string;
};
```

## 推荐文件结构

此项目的根目录为当前工作区的2/experiment/3/project。

请按以下结构创建项目文件：

```txt
project/
├─ package.json
├─ index.html
├─ tsconfig.json
├─ vite.config.ts
├─ src/
│  ├─ main.tsx
│  ├─ App.tsx
│  ├─ styles.css
│  ├─ types.ts
│  ├─ utils/
│  │  ├─ storage.ts
│  │  └─ date.ts
│  └─ components/
│     ├─ AssignmentForm.tsx
│     ├─ AssignmentFilters.tsx
│     └─ AssignmentList.tsx
```

## 开发要求

请严格按以下顺序输出：

### 第一步：开发计划

先简要说明开发计划，包括：

1. 项目结构
2. 状态管理方式
3. localStorage 持久化方案
4. 筛选、搜索、排序逻辑
5. 逾期和临近截止的判断逻辑

### 第二步：创建完整项目文件

然后输出每个文件的完整代码。

要求：

* 每个文件使用清晰的文件路径标题
* 代码必须完整
* 不要省略关键代码
* 不要写伪代码
* TypeScript 类型要明确
* React 组件拆分合理
* 样式要完整可用

### 第三步：启动和测试说明

最后说明如何启动项目：

```bash
npm install
npm run dev
```

并说明如何测试以下功能：

1. 添加作业
2. 刷新页面后数据是否保留
3. 按课程筛选
4. 按完成状态筛选
5. 搜索作业
6. 排序
7. 删除作业
8. 逾期任务高亮
9. 临近截止提醒

## 额外要求

* 代码风格简洁现代
* 不要引入 Redux、后端数据库或复杂依赖
* 不要使用 mock API
* 不要使用 any
* 不要生成无关说明
