import type { Metadata } from "next";
import Link from "next/link";
import { ArrowRight, ExternalLink } from "lucide-react";
import { GithubIcon } from "@/components/icons";
import { StatCard } from "@/components/stats/stat-card";
import { DifficultyPie } from "@/components/stats/difficulty-pie";
import { TopicBar } from "@/components/stats/topic-bar";
import { DifficultyBadge } from "@/components/difficulty-badge";
import { TopicBadge } from "@/components/topic-badge";
import { getAllSolutions, getManifest, getSolutionBySlug } from "@/lib/solutions";
import { difficultyCounts, recentlySolved, topicCounts } from "@/lib/stats";
import { FEATURED_SLUGS, OWNER } from "@/lib/constants";

export const metadata: Metadata = {
  alternates: { canonical: "/" },
};

export default function HomePage() {
  const manifest = getManifest();
  const solutions = getAllSolutions();
  const diff = difficultyCounts(solutions);
  const topics = topicCounts(solutions);
  const recent = recentlySolved(solutions, 5);
  const featured = FEATURED_SLUGS
    .map((slug) => getSolutionBySlug(slug))
    .filter((s): s is NonNullable<ReturnType<typeof getSolutionBySlug>> => Boolean(s));

  return (
    <div className="mx-auto max-w-6xl px-4 py-10 sm:px-6 sm:py-14">
      <section className="flex flex-col gap-6 pb-12">
        <div className="inline-flex w-fit items-center gap-2 rounded-full border border-border bg-muted/60 px-3 py-1 text-xs text-muted-foreground">
          <span className="h-1.5 w-1.5 rounded-full bg-[var(--easy)]" />
          <span>{manifest.total} problems solved · C++</span>
        </div>
        <h1 className="text-3xl font-semibold tracking-tight sm:text-5xl">
          A worked-out collection of <br className="hidden sm:block" />
          <span className="text-accent">LeetCode solutions in C++</span>
        </h1>
        <p className="max-w-2xl text-base text-muted-foreground sm:text-lg">
          Every solution has the approach explained, complexity analysis, and clean
          source — written by {OWNER.name.split(" ")[0]} while studying data
          structures and algorithms.
        </p>
        <div className="flex flex-wrap items-center gap-3">
          <Link
            href="/problems"
            className="inline-flex h-10 items-center gap-2 rounded-md bg-foreground px-4 text-sm font-medium text-background transition-opacity hover:opacity-90"
          >
            Browse problems
            <ArrowRight className="h-4 w-4" />
          </Link>
          <a
            href={OWNER.repo}
            target="_blank"
            rel="noreferrer noopener"
            className="inline-flex h-10 items-center gap-2 rounded-md border border-border bg-card px-4 text-sm font-medium text-foreground transition-colors hover:bg-muted"
          >
            <GithubIcon className="h-4 w-4" />
            View source
          </a>
        </div>
      </section>

      <section className="grid grid-cols-2 gap-3 sm:grid-cols-4">
        <StatCard label="Total" value={manifest.total} hint="Solutions" />
        {diff.map((d) => (
          <StatCard
            key={d.difficulty}
            label={d.difficulty}
            value={d.count}
            accent={
              d.difficulty === "Easy"
                ? "easy"
                : d.difficulty === "Medium"
                  ? "medium"
                  : "hard"
            }
          />
        ))}
      </section>

      <section className="mt-8 grid gap-6 lg:grid-cols-5">
        <div className="rounded-xl border border-border bg-card p-5 lg:col-span-2">
          <h2 className="mb-1 text-sm font-semibold">Difficulty mix</h2>
          <p className="mb-3 text-xs text-muted-foreground">
            Distribution of solved problems by difficulty.
          </p>
          <DifficultyPie data={diff} />
        </div>
        <div className="rounded-xl border border-border bg-card p-5 lg:col-span-3">
          <h2 className="mb-1 text-sm font-semibold">By topic</h2>
          <p className="mb-3 text-xs text-muted-foreground">
            Algorithmic patterns I&apos;ve practiced most.
          </p>
          <TopicBar data={topics.map((t) => ({ label: t.label, count: t.count }))} />
        </div>
      </section>

      {featured.length > 0 ? (
        <section className="mt-10">
          <div className="mb-3 flex items-end justify-between">
            <h2 className="text-lg font-semibold">Featured solutions</h2>
            <Link
              href="/problems"
              className="text-xs text-muted-foreground hover:text-foreground"
            >
              See all →
            </Link>
          </div>
          <div className="grid gap-3 md:grid-cols-3">
            {featured.map((s) => (
              <Link
                key={s.slug}
                href={`/problems/${s.slug}`}
                className="group flex flex-col gap-3 rounded-xl border border-border bg-card p-5 transition-colors hover:border-accent"
              >
                <div className="flex items-center justify-between gap-2">
                  <span className="font-mono text-xs text-muted-foreground">
                    #{s.paddedNumber}
                  </span>
                  <DifficultyBadge difficulty={s.difficulty} />
                </div>
                <h3 className="text-base font-semibold leading-snug group-hover:text-accent">
                  {s.title}
                </h3>
                <p className="line-clamp-2 text-xs text-muted-foreground">
                  {s.approach.keyInsight ?? s.approach.summary ?? s.description}
                </p>
                <div className="mt-auto flex items-center justify-between">
                  <TopicBadge topic={s.topic} asLink={false} />
                  <span className="font-mono text-xs text-muted-foreground">
                    {s.approach.timeComplexity ?? ""}
                  </span>
                </div>
              </Link>
            ))}
          </div>
        </section>
      ) : null}

      {recent.length > 0 ? (
        <section className="mt-10 rounded-xl border border-border bg-card">
          <div className="flex items-center justify-between border-b border-border px-5 py-3">
            <h2 className="text-sm font-semibold">Recently solved</h2>
            <Link
              href="/problems?s=newest"
              className="text-xs text-muted-foreground hover:text-foreground"
            >
              View timeline →
            </Link>
          </div>
          <ul className="divide-y divide-border">
            {recent.map((s) => (
              <li key={s.slug}>
                <Link
                  href={`/problems/${s.slug}`}
                  className="flex items-center gap-4 px-5 py-3 transition-colors hover:bg-muted/60"
                >
                  <span className="font-mono text-xs text-muted-foreground">
                    #{s.paddedNumber}
                  </span>
                  <span className="flex-1 text-sm font-medium">{s.title}</span>
                  <DifficultyBadge difficulty={s.difficulty} className="hidden sm:inline-flex" />
                  <TopicBadge topic={s.topic} asLink={false} className="hidden md:inline-flex" />
                  <span className="hidden text-xs text-muted-foreground sm:inline">
                    {s.firstCommittedAt?.slice(0, 10)}
                  </span>
                  <ExternalLink className="h-3.5 w-3.5 text-muted-foreground" />
                </Link>
              </li>
            ))}
          </ul>
        </section>
      ) : null}
    </div>
  );
}
