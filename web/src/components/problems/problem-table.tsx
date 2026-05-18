"use client";

import { useEffect, useMemo, useState } from "react";
import { useRouter, useSearchParams } from "next/navigation";
import Link from "next/link";
import { ChevronRight, Search } from "lucide-react";
import type { Difficulty, Solution, Topic } from "@/types/solution";
import { DifficultyBadge } from "@/components/difficulty-badge";
import { TopicBadge } from "@/components/topic-badge";
import { TOPIC_LABELS, TOPIC_ORDER } from "@/lib/constants";

type DifficultyFilter = "All" | Difficulty;
type TopicFilter = "All" | Topic;
type SortKey = "number-asc" | "number-desc" | "difficulty" | "newest";

const DIFFICULTIES: DifficultyFilter[] = ["All", "Easy", "Medium", "Hard"];
const SORT_OPTIONS: { value: SortKey; label: string }[] = [
  { value: "number-asc", label: "Number ↑" },
  { value: "number-desc", label: "Number ↓" },
  { value: "difficulty", label: "Difficulty" },
  { value: "newest", label: "Recently solved" },
];

const DIFF_RANK: Record<Difficulty, number> = { Easy: 0, Medium: 1, Hard: 2 };

export function ProblemTable({ solutions }: { solutions: Solution[] }) {
  const router = useRouter();
  const search = useSearchParams();

  const [query, setQuery] = useState(() => search.get("q") ?? "");
  const [difficulty, setDifficulty] = useState<DifficultyFilter>(
    () => normalizeDifficulty(search.get("d")),
  );
  const [topic, setTopic] = useState<TopicFilter>(() => normalizeTopic(search.get("t")));
  const [sort, setSort] = useState<SortKey>(() => normalizeSort(search.get("s")));

  // Sync URL search params on filter change (replace, not push, to avoid history pollution).
  useEffect(() => {
    const params = new URLSearchParams();
    if (query.trim()) params.set("q", query.trim());
    if (difficulty !== "All") params.set("d", difficulty);
    if (topic !== "All") params.set("t", topic);
    if (sort !== "number-asc") params.set("s", sort);
    const qs = params.toString();
    router.replace(qs ? `/problems?${qs}` : "/problems", { scroll: false });
  }, [query, difficulty, topic, sort, router]);

  const filtered = useMemo(() => {
    const q = query.trim().toLowerCase();
    let list = solutions.filter((s) => {
      if (difficulty !== "All" && s.difficulty !== difficulty) return false;
      if (topic !== "All" && s.topic !== topic) return false;
      if (q) {
        const haystack = `${s.number} ${s.title} ${s.topicLabel}`.toLowerCase();
        if (!haystack.includes(q)) return false;
      }
      return true;
    });
    list = [...list].sort((a, b) => {
      switch (sort) {
        case "number-desc":
          return b.number - a.number;
        case "difficulty":
          return DIFF_RANK[a.difficulty] - DIFF_RANK[b.difficulty] || a.number - b.number;
        case "newest":
          return (b.firstCommittedAt ?? "").localeCompare(a.firstCommittedAt ?? "");
        case "number-asc":
        default:
          return a.number - b.number;
      }
    });
    return list;
  }, [solutions, query, difficulty, topic, sort]);

  const availableTopics = useMemo(() => {
    const present = new Set(solutions.map((s) => s.topic));
    return TOPIC_ORDER.filter((t) => present.has(t));
  }, [solutions]);

  return (
    <div className="flex flex-col gap-6">
      <Filters
        query={query}
        setQuery={setQuery}
        difficulty={difficulty}
        setDifficulty={setDifficulty}
        topic={topic}
        setTopic={setTopic}
        sort={sort}
        setSort={setSort}
        availableTopics={availableTopics}
      />

      <div className="flex items-baseline gap-2 text-xs text-muted-foreground">
        <span>
          {filtered.length} of {solutions.length} problems
        </span>
        {(difficulty !== "All" || topic !== "All" || query.trim() || sort !== "number-asc") ? (
          <button
            type="button"
            onClick={() => {
              setQuery("");
              setDifficulty("All");
              setTopic("All");
              setSort("number-asc");
            }}
            className="text-foreground underline-offset-4 hover:underline"
          >
            Reset
          </button>
        ) : null}
      </div>

      {filtered.length === 0 ? (
        <div className="rounded-xl border border-dashed border-border bg-card/50 p-12 text-center text-sm text-muted-foreground">
          No problems match those filters.
        </div>
      ) : (
        <ul className="overflow-hidden rounded-xl border border-border bg-card">
          {filtered.map((s) => (
            <li key={s.slug} className="border-b border-border last:border-b-0">
              <Link
                href={`/problems/${s.slug}`}
                className="grid grid-cols-[auto_1fr_auto] items-center gap-3 px-4 py-3 transition-colors hover:bg-muted/60 sm:grid-cols-[auto_1fr_auto_auto_auto_auto] sm:px-5 sm:py-3.5"
              >
                <span className="font-mono text-xs text-muted-foreground">
                  #{s.paddedNumber}
                </span>
                <span className="min-w-0 truncate text-sm font-medium">
                  {s.title}
                </span>
                <span className="hidden font-mono text-xs text-muted-foreground sm:inline">
                  {s.approach.timeComplexity ?? ""}
                </span>
                <TopicBadge
                  topic={s.topic}
                  asLink={false}
                  className="hidden sm:inline-flex"
                />
                <DifficultyBadge
                  difficulty={s.difficulty}
                  className="hidden sm:inline-flex"
                />
                <ChevronRight className="h-4 w-4 text-muted-foreground" aria-hidden />
              </Link>
            </li>
          ))}
        </ul>
      )}
    </div>
  );
}

interface FilterProps {
  query: string;
  setQuery: (v: string) => void;
  difficulty: DifficultyFilter;
  setDifficulty: (v: DifficultyFilter) => void;
  topic: TopicFilter;
  setTopic: (v: TopicFilter) => void;
  sort: SortKey;
  setSort: (v: SortKey) => void;
  availableTopics: Topic[];
}

function Filters({
  query,
  setQuery,
  difficulty,
  setDifficulty,
  topic,
  setTopic,
  sort,
  setSort,
  availableTopics,
}: FilterProps) {
  return (
    <div className="flex flex-col gap-3">
      <div className="relative">
        <Search
          className="pointer-events-none absolute left-3 top-1/2 h-4 w-4 -translate-y-1/2 text-muted-foreground"
          aria-hidden
        />
        <input
          type="search"
          value={query}
          onChange={(e) => setQuery(e.target.value)}
          placeholder="Search by problem number or title..."
          className="h-10 w-full rounded-md border border-border bg-card pl-9 pr-3 text-sm shadow-sm transition-colors placeholder:text-muted-foreground focus:border-accent focus:outline-none"
        />
      </div>

      <div className="flex flex-wrap items-center gap-2">
        <div className="inline-flex overflow-hidden rounded-md border border-border bg-card text-xs">
          {DIFFICULTIES.map((d) => (
            <button
              key={d}
              type="button"
              onClick={() => setDifficulty(d)}
              data-active={difficulty === d}
              className="border-r border-border px-3 py-1.5 text-muted-foreground transition-colors last:border-r-0 hover:bg-muted hover:text-foreground data-[active=true]:bg-foreground data-[active=true]:text-background"
            >
              {d}
            </button>
          ))}
        </div>

        <select
          value={topic}
          onChange={(e) => setTopic(e.target.value as TopicFilter)}
          className="h-8 rounded-md border border-border bg-card px-2 text-xs text-foreground focus:border-accent focus:outline-none"
        >
          <option value="All">All topics</option>
          {availableTopics.map((t) => (
            <option key={t} value={t}>
              {TOPIC_LABELS[t]}
            </option>
          ))}
        </select>

        <select
          value={sort}
          onChange={(e) => setSort(e.target.value as SortKey)}
          className="ml-auto h-8 rounded-md border border-border bg-card px-2 text-xs text-foreground focus:border-accent focus:outline-none"
        >
          {SORT_OPTIONS.map((o) => (
            <option key={o.value} value={o.value}>
              Sort: {o.label}
            </option>
          ))}
        </select>
      </div>
    </div>
  );
}

function normalizeDifficulty(v: string | null): DifficultyFilter {
  if (v === "Easy" || v === "Medium" || v === "Hard") return v;
  return "All";
}

function normalizeTopic(v: string | null): TopicFilter {
  if (!v) return "All";
  if ((TOPIC_ORDER as string[]).includes(v)) return v as Topic;
  return "All";
}

function normalizeSort(v: string | null): SortKey {
  if (v === "number-desc" || v === "difficulty" || v === "newest") return v;
  return "number-asc";
}
