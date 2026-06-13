import type { Assignment, Priority } from "../types";
import { isValidDateOnly, isValidDateTime } from "./date";

const STORAGE_KEY = "course-assignment-manager:assignments:v1";

const priorities: Priority[] = ["low", "medium", "high"];

function isRecord(value: unknown): value is Record<string, unknown> {
  return typeof value === "object" && value !== null;
}

function isPriority(value: unknown): value is Priority {
  return typeof value === "string" && priorities.includes(value as Priority);
}

function isAssignment(value: unknown): value is Assignment {
  if (!isRecord(value)) {
    return false;
  }

  return (
    typeof value.id === "string" &&
    typeof value.course === "string" &&
    value.course.trim().length > 0 &&
    typeof value.title === "string" &&
    value.title.trim().length > 0 &&
    typeof value.dueDate === "string" &&
    isValidDateOnly(value.dueDate) &&
    typeof value.completed === "boolean" &&
    isPriority(value.priority) &&
    typeof value.createdAt === "string" &&
    isValidDateTime(value.createdAt)
  );
}

function getLocalStorage(): Storage | null {
  try {
    return typeof window === "undefined" ? null : window.localStorage;
  } catch {
    return null;
  }
}

export function loadAssignments(): Assignment[] {
  const storage = getLocalStorage();

  if (storage === null) {
    return [];
  }


  try {
    const raw = storage.getItem(STORAGE_KEY);

    if (raw === null) {
      return [];
    }

    const parsed: unknown = JSON.parse(raw);
    return Array.isArray(parsed) ? parsed.filter(isAssignment) : [];
  } catch {
    return [];
  }
}

export function saveAssignments(assignments: Assignment[]): boolean {
  const storage = getLocalStorage();

  if (storage === null) {
    return false;
  }

  try {
    storage.setItem(STORAGE_KEY, JSON.stringify(assignments));
    return true;
  } catch {
    return false;
  }
}
