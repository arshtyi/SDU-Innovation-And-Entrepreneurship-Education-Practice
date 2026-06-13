import type { Assignment, Priority } from "../types";
import { formatDueDate, getDueHint, isDueSoon, isOverdue } from "../utils/date";

type AssignmentListProps = {
  assignments: Assignment[];
  onToggleCompleted: (id: string) => void;
  onDelete: (id: string) => void;
};

const priorityLabels: Record<Priority, string> = {
  low: "低优先级",
  medium: "中优先级",
  high: "高优先级",
};

export default function AssignmentList({
  assignments,
  onToggleCompleted,
  onDelete,
}: AssignmentListProps) {
  if (assignments.length === 0) {
    return (
      <div className="empty-state">
        <h3>暂时没有匹配的作业</h3>
        <p>添加一项课程作业，或调整筛选和搜索条件。</p>
      </div>
    );
  }

  return (
    <div className="assignment-list">
      {assignments.map((assignment) => {
        const overdue = isOverdue(assignment.dueDate, assignment.completed);
        const dueSoon = isDueSoon(assignment.dueDate, assignment.completed);
        const cardClassName = [
          "assignment-card",
          `priority-${assignment.priority}`,
          assignment.completed ? "is-completed" : "",
          overdue ? "is-overdue" : "",
          dueSoon ? "is-due-soon" : "",
        ]
          .filter(Boolean)
          .join(" ");

        return (
          <article className={cardClassName} key={assignment.id}>
            <div className="assignment-main">
              <div>
                <div className="card-meta">
                  <span>{assignment.course}</span>
                  <span className={`priority-badge priority-badge-${assignment.priority}`}>
                    {priorityLabels[assignment.priority]}
                  </span>
                </div>
                <h3>{assignment.title}</h3>
              </div>

              <div className="card-actions">
                <button
                  className="secondary-button"
                  type="button"
                  onClick={() => onToggleCompleted(assignment.id)}
                >
                  {assignment.completed ? "设为未完成" : "标记完成"}
                </button>
                <button
                  className="danger-button"
                  type="button"
                  onClick={() => onDelete(assignment.id)}
                >
                  删除
                </button>
              </div>
            </div>

            <div className="card-footer">
              <span>截止：{formatDueDate(assignment.dueDate)}</span>
              <span
                className={
                  overdue ? "due-hint overdue-text" : dueSoon ? "due-hint soon-text" : "due-hint"
                }
              >
                {getDueHint(assignment.dueDate, assignment.completed)}
              </span>
            </div>

            {overdue && <div className="alert alert-overdue">逾期未完成，请优先处理。</div>}
            {dueSoon && !overdue && (
              <div className="alert alert-soon">距离截止日期 3 天内，请尽快完成。</div>
            )}
          </article>
        );
      })}
    </div>
  );
}
