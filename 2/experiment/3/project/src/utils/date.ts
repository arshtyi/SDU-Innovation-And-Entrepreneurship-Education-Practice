const DAY_IN_MS = 24 * 60 * 60 * 1000;
const DATE_ONLY_PATTERN = /^(\d{4})-(\d{2})-(\d{2})$/;

export function parseDateOnly(value: string): Date {
  const [year, month, day] = value.split("-").map(Number);
  return new Date(year, month - 1, day);
}

export function isValidDateOnly(value: string): boolean {
  const match = DATE_ONLY_PATTERN.exec(value);

  if (match === null) {
    return false;
  }

  const year = Number(match[1]);
  const month = Number(match[2]);
  const day = Number(match[3]);
  const parsed = new Date(year, month - 1, day);

  return (
    parsed.getFullYear() === year &&
    parsed.getMonth() === month - 1 &&
    parsed.getDate() === day
  );
}

export function isValidDateTime(value: string): boolean {
  return Number.isFinite(Date.parse(value));
}

export function startOfToday(now = new Date()): Date {
  return new Date(now.getFullYear(), now.getMonth(), now.getDate());
}

export function daysUntilDue(dueDate: string, now = new Date()): number {
  const dueTime = parseDateOnly(dueDate).getTime();
  const todayTime = startOfToday(now).getTime();
  return Math.ceil((dueTime - todayTime) / DAY_IN_MS);
}

export function isOverdue(dueDate: string, completed: boolean, now = new Date()): boolean {
  return !completed && daysUntilDue(dueDate, now) < 0;
}

export function isDueSoon(dueDate: string, completed: boolean, now = new Date()): boolean {
  const days = daysUntilDue(dueDate, now);
  return !completed && days >= 0 && days <= 3;
}

export function formatDueDate(dueDate: string): string {
  return new Intl.DateTimeFormat("zh-CN", {
    month: "long",
    day: "numeric",
    weekday: "short",
  }).format(parseDateOnly(dueDate));
}

export function getDueHint(dueDate: string, completed: boolean): string {
  if (completed) {
    return "已完成";
  }

  const days = daysUntilDue(dueDate);

  if (days < 0) {
    return `已逾期 ${Math.abs(days)} 天`;
  }

  if (days === 0) {
    return "今天截止";
  }

  return `${days} 天后截止`;
}
