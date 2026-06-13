export type Priority = "low" | "medium" | "high";

export type StatusFilter = "all" | "active" | "completed";

export type SortDirection = "asc" | "desc";

export type Assignment = {
  id: string;
  course: string;
  title: string;
  dueDate: string;
  completed: boolean;
  priority: Priority;
  createdAt: string;
};

export type AssignmentInput = Omit<Assignment, "id" | "createdAt">;
