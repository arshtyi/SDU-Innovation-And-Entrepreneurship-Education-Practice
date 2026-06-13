import { useState } from "react";
import type { AssignmentInput, Priority } from "../types";

type AssignmentFormProps = {
  onAdd: (input: AssignmentInput) => void;
};

type FormErrors = {
  course?: string;
  title?: string;
  dueDate?: string;
};

const priorityOptions: Array<{ value: Priority; label: string }> = [
  { value: "low", label: "低" },
  { value: "medium", label: "中" },
  { value: "high", label: "高" },
];

export default function AssignmentForm({ onAdd }: AssignmentFormProps) {
  const [course, setCourse] = useState("");
  const [title, setTitle] = useState("");
  const [dueDate, setDueDate] = useState("");
  const [priority, setPriority] = useState<Priority>("medium");
  const [completed, setCompleted] = useState(false);
  const [errors, setErrors] = useState<FormErrors>({});

  function validate(): FormErrors {
    const nextErrors: FormErrors = {};

    if (course.trim().length === 0) {
      nextErrors.course = "请输入课程名";
    }

    if (title.trim().length === 0) {
      nextErrors.title = "请输入作业标题";
    }

    if (dueDate.length === 0) {
      nextErrors.dueDate = "请选择截止日期";
    }

    return nextErrors;
  }

  function handleSubmit(event: React.FormEvent<HTMLFormElement>): void {
    event.preventDefault();

    const nextErrors = validate();
    setErrors(nextErrors);

    if (Object.keys(nextErrors).length > 0) {
      return;
    }

    onAdd({
      course: course.trim(),
      title: title.trim(),
      dueDate,
      completed,
      priority,
    });

    setCourse("");
    setTitle("");
    setDueDate("");
    setPriority("medium");
    setCompleted(false);
    setErrors({});
  }

  return (
    <form className="assignment-form" onSubmit={handleSubmit} noValidate>
      <label>
        <span>课程名</span>
        <input
          value={course}
          onChange={(event) => setCourse(event.target.value)}
          placeholder="例如：创新创业实践"
          aria-invalid={Boolean(errors.course)}
        />
        {errors.course && <strong className="field-error">{errors.course}</strong>}
      </label>

      <label>
        <span>作业标题</span>
        <input
          value={title}
          onChange={(event) => setTitle(event.target.value)}
          placeholder="例如：商业计划书初稿"
          aria-invalid={Boolean(errors.title)}
        />
        {errors.title && <strong className="field-error">{errors.title}</strong>}
      </label>

      <label>
        <span>截止日期</span>
        <input
          type="date"
          value={dueDate}
          onChange={(event) => setDueDate(event.target.value)}
          aria-invalid={Boolean(errors.dueDate)}
        />
        {errors.dueDate && <strong className="field-error">{errors.dueDate}</strong>}
      </label>

      <label>
        <span>优先级</span>
        <select value={priority} onChange={(event) => setPriority(event.target.value as Priority)}>
          {priorityOptions.map((option) => (
            <option key={option.value} value={option.value}>
              {option.label}
            </option>
          ))}
        </select>
      </label>

      <label className="checkbox-row">
        <input
          type="checkbox"
          checked={completed}
          onChange={(event) => setCompleted(event.target.checked)}
        />
        <span>添加时标记为已完成</span>
      </label>

      <button className="primary-button" type="submit">
        添加作业
      </button>
    </form>
  );
}
