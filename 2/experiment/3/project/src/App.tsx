import { useEffect, useMemo, useState } from "react";
import AssignmentFilters from "./components/AssignmentFilters";
import AssignmentForm from "./components/AssignmentForm";
import AssignmentList from "./components/AssignmentList";
import type { Assignment, AssignmentInput, SortDirection, StatusFilter } from "./types";
import { parseDateOnly } from "./utils/date";
import { loadAssignments, saveAssignments } from "./utils/storage";

function createAssignmentId(): string {
  if (typeof crypto !== "undefined" && typeof crypto.randomUUID === "function") {
    return crypto.randomUUID();
  }

  return `${Date.now()}-${Math.random().toString(16).slice(2)}`;
}

export default function App() {
  const [assignments, setAssignments] = useState<Assignment[]>(() => loadAssignments());
  const [courseFilter, setCourseFilter] = useState("all");
  const [statusFilter, setStatusFilter] = useState<StatusFilter>("all");
  const [query, setQuery] = useState("");
  const [sortDirection, setSortDirection] = useState<SortDirection>("asc");
  const [storageError, setStorageError] = useState(false);

  useEffect(() => {
    setStorageError(!saveAssignments(assignments));
  }, [assignments]);

  const courses = useMemo(() => {
    return Array.from(new Set(assignments.map((assignment) => assignment.course))).sort((a, b) =>
      a.localeCompare(b, "zh-CN"),
    );
  }, [assignments]);

  useEffect(() => {
    if (courseFilter !== "all" && !courses.includes(courseFilter)) {
      setCourseFilter("all");
    }
  }, [courseFilter, courses]);

  const visibleAssignments = useMemo(() => {
    const keyword = query.trim().toLowerCase();

    return assignments
      .filter((assignment) => courseFilter === "all" || assignment.course === courseFilter)
      .filter((assignment) => {
        if (statusFilter === "active") {
          return !assignment.completed;
        }

        if (statusFilter === "completed") {
          return assignment.completed;
        }

        return true;
      })
      .filter((assignment) => {
        if (keyword.length === 0) {
          return true;
        }

        const course = assignment.course.toLowerCase();
        const title = assignment.title.toLowerCase();
        return course.includes(keyword) || title.includes(keyword);
      })
      .sort((left, right) => {
        const leftDueTime = parseDateOnly(left.dueDate).getTime();
        const rightDueTime = parseDateOnly(right.dueDate).getTime();
        const dueDiff = leftDueTime - rightDueTime;
        const createdDiff =
          new Date(left.createdAt).getTime() - new Date(right.createdAt).getTime();
        const result = dueDiff === 0 ? createdDiff : dueDiff;
        return sortDirection === "asc" ? result : -result;
      });
  }, [assignments, courseFilter, query, sortDirection, statusFilter]);

  const activeCount = assignments.filter((assignment) => !assignment.completed).length;
  const completedCount = assignments.length - activeCount;

  function handleAddAssignment(input: AssignmentInput): void {
    const nextAssignment: Assignment = {
      ...input,
      id: createAssignmentId(),
      createdAt: new Date().toISOString(),
    };

    setAssignments((current) => [nextAssignment, ...current]);
  }

  function handleToggleCompleted(id: string): void {
    setAssignments((current) =>
      current.map((assignment) =>
        assignment.id === id
          ? { ...assignment, completed: !assignment.completed }
          : assignment,
      ),
    );
  }

  function handleDeleteAssignment(id: string): void {
    const confirmed = window.confirm("确定要删除这项作业吗？此操作无法撤销。");

    if (!confirmed) {
      return;
    }

    setAssignments((current) => current.filter((assignment) => assignment.id !== id));
  }

  return (
    <div className="app">
      <header className="app-header">
        <div>
          <p className="eyebrow">Assignment Tracker</p>
          <h1>课程作业提交管理小工具</h1>
        </div>
        <div className="summary" aria-label="作业统计">
          <span>{assignments.length} 项作业</span>
          <span>{activeCount} 项未完成</span>
          <span>{completedCount} 项已完成</span>
        </div>
      </header>

      {storageError && (
        <div className="storage-alert" role="status">
          本地保存当前不可用。你仍可临时管理作业，但刷新页面后更改可能不会保留。
        </div>
      )}

      <main className="app-shell">
        <section className="form-panel" aria-labelledby="form-title">
          <h2 id="form-title">添加作业</h2>
          <AssignmentForm onAdd={handleAddAssignment} />
        </section>

        <section className="list-panel" aria-labelledby="list-title">
          <div className="panel-title-row">
            <div>
              <h2 id="list-title">作业列表</h2>
              <p>筛选、搜索和整理近期课程任务。</p>
            </div>
            <span className="result-count">{visibleAssignments.length} 条结果</span>
          </div>

          <AssignmentFilters
            courses={courses}
            courseFilter={courseFilter}
            statusFilter={statusFilter}
            query={query}
            sortDirection={sortDirection}
            onCourseFilterChange={setCourseFilter}
            onStatusFilterChange={setStatusFilter}
            onQueryChange={setQuery}
            onSortDirectionChange={setSortDirection}
          />

          <AssignmentList
            assignments={visibleAssignments}
            onToggleCompleted={handleToggleCompleted}
            onDelete={handleDeleteAssignment}
          />
        </section>
      </main>
    </div>
  );
}
