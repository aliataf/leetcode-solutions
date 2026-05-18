import Link from "next/link";
import type { Topic } from "@/types/solution";
import { TOPIC_LABELS } from "@/lib/constants";
import { cn } from "@/lib/cn";

export function TopicBadge({
  topic,
  asLink = true,
  className,
}: {
  topic: Topic;
  asLink?: boolean;
  className?: string;
}) {
  const styles = cn(
    "inline-flex items-center rounded-md border border-border bg-muted/60 px-2 py-0.5 text-xs font-medium text-muted-foreground transition-colors",
    asLink && "hover:bg-muted hover:text-foreground",
    className,
  );
  if (!asLink) {
    return <span className={styles}>{TOPIC_LABELS[topic]}</span>;
  }
  return (
    <Link href={`/problems?t=${topic}`} className={styles}>
      {TOPIC_LABELS[topic]}
    </Link>
  );
}
