import type { Difficulty } from "@/types/solution";
import { cn } from "@/lib/cn";

const STYLES: Record<Difficulty, string> = {
  Easy: "bg-[var(--easy-bg)] text-[var(--easy)]",
  Medium: "bg-[var(--medium-bg)] text-[var(--medium)]",
  Hard: "bg-[var(--hard-bg)] text-[var(--hard)]",
};

export function DifficultyBadge({
  difficulty,
  className,
}: {
  difficulty: Difficulty;
  className?: string;
}) {
  return (
    <span
      className={cn(
        "inline-flex items-center rounded-full px-2 py-0.5 text-xs font-medium",
        STYLES[difficulty],
        className,
      )}
    >
      {difficulty}
    </span>
  );
}
