# 3

## 计划

可行，范围是纯前端 SPA，不需要后端。状态用 React `useState` 管理，`useMemo` 派生筛选结果；`localStorage` 通过 `src/utils/storage.ts` 统一读写。筛选逻辑包含课程、完成状态、关键词搜索；排序按 `dueDate` 升序或降序。日期判断集中在 `src/utils/date.ts`：截止日期小于今天且未完成为逾期；距离今天 0 到 3 天且未完成为临近截止。

## 目录结构

```txt
project
├── index.html
├── package.json
├── src
│   ├── App.tsx
│   ├── components
│   │   ├── AssignmentFilters.tsx
│   │   ├── AssignmentForm.tsx
│   │   └── AssignmentList.tsx
│   ├── main.tsx
│   ├── styles.css
│   ├── types.ts
│   └── utils
│       ├── date.ts
│       └── storage.ts
├── tsconfig.json
└── vite.config.ts
```

## 首次运行

```powershell
npm install
npm run dev
```

打开

```text
http://127.0.0.1:5173
```

成功
