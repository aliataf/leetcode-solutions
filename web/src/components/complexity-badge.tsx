import { Clock, HardDrive } from "lucide-react";
import { cn } from "@/lib/cn";

interface Props {
  kind: "time" | "space";
  expression: string;
  note?: string;
  className?: string;
}

export function ComplexityBadge({ kind, expression, note, className }: Props) {
  const Icon = kind === "time" ? Clock : HardDrive;
  const label = kind === "time" ? "Time" : "Space";
  return (
    <div
      className={cn(
        "flex items-start gap-2 rounded-lg border border-border bg-card p-3",
        className,
      )}
    >
      <div className="mt-0.5 inline-flex h-6 w-6 shrink-0 items-center justify-center rounded-md bg-muted text-muted-foreground">
        <Icon className="h-3.5 w-3.5" aria-hidden />
      </div>
      <div className="min-w-0">
        <div className="text-xs uppercase tracking-wide text-muted-foreground">
          {label}
        </div>
        <div className="font-mono text-sm font-semibold text-foreground">
          {expression}
        </div>
        {note ? (
          <div className="mt-0.5 text-xs leading-snug text-muted-foreground">
            {note}
          </div>
        ) : null}
      </div>
    </div>
  );
}
