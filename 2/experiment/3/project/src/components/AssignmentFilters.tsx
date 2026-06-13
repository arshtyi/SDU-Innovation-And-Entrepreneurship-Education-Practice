import type { SortDirection, StatusFilter } from "../types";

type AssignmentFiltersProps = {
  courses: string[];
  courseFilter: string;
  statusFilter: StatusFilter;
  query: string;
  sortDirection: SortDirection;
  onCourseFilterChange: (value: string) => void;
  onStatusFilterChange: (value: StatusFilter) => void;
  onQueryChange: (value: string) => void;
  onSortDirectionChange: (value: SortDirection) => void;
};

export default function AssignmentFilters({
  courses,
  courseFilter,
  statusFilter,
  query,
  sortDirection,
  onCourseFilterChange,
  onStatusFilterChange,
  onQueryChange,
  onSortDirectionChange,
}: AssignmentFiltersProps) {
  return (
    <div className="filters" aria-label="作业筛选">
      <label className="search-field">
        <span>搜索</span>
        <input
          value={query}
          onChange={(event) => onQueryChange(event.target.value)}
          placeholder="搜索作业标题或课程名"
        />
      </label>

      <label>
        <span>课程</span>
        <select value={courseFilter} onChange={(event) => onCourseFilterChange(event.target.value)}>
          <option value="all">全部课程</option>
          {courses.map((course) => (
            <option key={course} value={course}>
              {course}
            </option>
          ))}
        </select>
      </label>

      <label>
        <span>状态</span>
        <select
          value={statusFilter}
          onChange={(event) => onStatusFilterChange(event.target.value as StatusFilter)}
        >
          <option value="all">全部</option>
          <option value="active">未完成</option>
          <option value="completed">已完成</option>
        </select>
      </label>

      <label className="sort-field">
        <span>排序</span>
        <select
          value={sortDirection}
          onChange={(event) => onSortDirectionChange(event.target.value as SortDirection)}
        >
          <option value="asc">截止日期从近到远</option>
          <option value="desc">截止日期从远到近</option>
        </select>
      </label>
    </div>
  );
}
