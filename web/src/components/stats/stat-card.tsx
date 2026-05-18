import type { ReactNode } from "react";
import { cn } from "@/lib/cn";

interface Props {
  label: string;
  value: ReactNode;
  hint?: string;
  accent?: "default" | "easy" | "medium" | "hard";
  className?: string;
}

const ACCENT: Record<NonNullable<Props["accent"]>, string> = {
  default: "text-foreground",
  easy: "text-[var(--easy)]",
  medium: "text-[var(--medium)]",
  hard: "text-[var(--hard)]",
};

export function StatCard({
  label,
  value,
  hint,
  accent = "default",
  className,
}: Props) {
  return (
    <div
      className={cn(
        "rounded-xl border border-border bg-card p-5 transition-colors",
        className,
      )}
    >
      <div className="text-xs font-medium uppercase tracking-wider text-muted-foreground">
        {label}
      </div>
      <div className={cn("mt-1 text-3xl font-semibold tabular-nums", ACCENT[accent])}>
        {value}
      </div>
      {hint ? (
        <div className="mt-1 text-xs text-muted-foreground">{hint}</div>
      ) : null}
    </div>
  );
}
