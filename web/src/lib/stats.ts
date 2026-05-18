import type { Difficulty, Solution, Topic } from "@/types/solution";
import { TOPIC_LABELS, TOPIC_ORDER } from "@/lib/constants";

export interface TopicCount {
  topic: Topic;
  label: string;
  count: number;
}

export function topicCounts(solutions: Solution[]): TopicCount[] {
  const counts = new Map<Topic, number>();
  for (const s of solutions) counts.set(s.topic, (counts.get(s.topic) ?? 0) + 1);
  return TOPIC_ORDER.filter((t) => (counts.get(t) ?? 0) > 0).map((topic) => ({
    topic,
    label: TOPIC_LABELS[topic],
    count: counts.get(topic) ?? 0,
  }));
}

export interface DifficultyCount {
  difficulty: Difficulty;
  count: number;
}

export function difficultyCounts(solutions: Solution[]): DifficultyCount[] {
  const counts: Record<Difficulty, number> = { Easy: 0, Medium: 0, Hard: 0 };
  for (const s of solutions) counts[s.difficulty] += 1;
  return (Object.keys(counts) as Difficulty[]).map((difficulty) => ({
    difficulty,
    count: counts[difficulty],
  }));
}

export function monthlyActivity(solutions: Solution[]) {
  const buckets = new Map<string, number>();
  for (const s of solutions) {
    if (!s.firstCommittedAt) continue;
    const key = s.firstCommittedAt.slice(0, 7);
    buckets.set(key, (buckets.get(key) ?? 0) + 1);
  }
  return [...buckets.entries()]
    .sort(([a], [b]) => a.localeCompare(b))
    .map(([month, count]) => ({ month, count }));
}

export function recentlySolved(solutions: Solution[], limit: number = 5): Solution[] {
  return [...solutions]
    .filter((s) => s.firstCommittedAt)
    .sort((a, b) => (a.firstCommittedAt! < b.firstCommittedAt! ? 1 : -1))
    .slice(0, limit);
}
