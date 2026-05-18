import type { Metadata } from "next";
import { notFound } from "next/navigation";
import Link from "next/link";
import { ArrowLeft, ExternalLink, Lightbulb } from "lucide-react";
import { DifficultyBadge } from "@/components/difficulty-badge";
import { TopicBadge } from "@/components/topic-badge";
import { ComplexityBadge } from "@/components/complexity-badge";
import { CodeBlock } from "@/components/code-block";
import { GithubIcon } from "@/components/icons";
import { getAllSlugs, getSolutionBySlug } from "@/lib/solutions";

interface PageParams {
  params: Promise<{ slug: string }>;
}

export function generateStaticParams() {
  return getAllSlugs().map((slug) => ({ slug }));
}

export async function generateMetadata({ params }: PageParams): Promise<Metadata> {
  const { slug } = await params;
  const s = getSolutionBySlug(slug);
  if (!s) return { title: "Not found" };
  return {
    title: `${s.number}. ${s.title}`,
    description: s.description.slice(0, 160) || `${s.title} — ${s.difficulty}`,
  };
}

export default async function ProblemPage({ params }: PageParams) {
  const { slug } = await params;
  const s = getSolutionBySlug(slug);
  if (!s) notFound();

  const solved = s.firstCommittedAt
    ? new Date(s.firstCommittedAt).toLocaleDateString("en-US", {
        year: "numeric",
        month: "long",
        day: "numeric",
      })
    : null;

  return (
    <article className="mx-auto max-w-4xl px-4 py-8 sm:px-6 sm:py-12">
      <nav className="mb-6 flex items-center gap-2 text-xs text-muted-foreground">
        <Link
          href="/problems"
          className="inline-flex items-center gap-1 hover:text-foreground"
        >
          <ArrowLeft className="h-3.5 w-3.5" />
          All problems
        </Link>
        <span aria-hidden>/</span>
        <span className="font-mono">#{s.paddedNumber}</span>
      </nav>

      <header className="flex flex-col gap-4 border-b border-border pb-6">
        <div className="flex flex-wrap items-center gap-2 text-xs text-muted-foreground">
          <span className="font-mono">#{s.paddedNumber}</span>
          <span>·</span>
          <DifficultyBadge difficulty={s.difficulty} />
          <TopicBadge topic={s.topic} />
        </div>
        <h1 className="text-3xl font-semibold tracking-tight sm:text-4xl">
          {s.title}
        </h1>
        <div className="flex flex-wrap items-center gap-2 text-xs">
          <a
            href={s.link}
            target="_blank"
            rel="noreferrer noopener"
            className="inline-flex items-center gap-1.5 rounded-md border border-border bg-card px-2.5 py-1 text-foreground transition-colors hover:bg-muted"
          >
            View on LeetCode
            <ExternalLink className="h-3 w-3" />
          </a>
          <a
            href={s.githubUrl}
            target="_blank"
            rel="noreferrer noopener"
            className="inline-flex items-center gap-1.5 rounded-md border border-border bg-card px-2.5 py-1 text-foreground transition-colors hover:bg-muted"
          >
            <GithubIcon className="h-3 w-3" />
            Source on GitHub
          </a>
        </div>
      </header>

      <section className="mt-8 flex flex-col gap-4">
        <div className="flex flex-col gap-1">
          <p className="text-xs uppercase tracking-wider text-muted-foreground">
            Approach
          </p>
          <h2 className="text-xl font-semibold">{s.approach.title}</h2>
        </div>

        {s.approach.keyInsight ? (
          <div className="flex items-start gap-3 rounded-xl border border-border bg-muted/40 p-4">
            <div className="mt-0.5 inline-flex h-6 w-6 shrink-0 items-center justify-center rounded-md bg-accent/15 text-accent">
              <Lightbulb className="h-3.5 w-3.5" aria-hidden />
            </div>
            <div className="min-w-0">
              <div className="text-xs font-semibold uppercase tracking-wide text-muted-foreground">
                Key insight
              </div>
              <p className="mt-1 whitespace-pre-line text-sm leading-relaxed text-foreground">
                {s.approach.keyInsight}
              </p>
            </div>
          </div>
        ) : null}

        {s.approach.summary && !s.approach.strategy ? (
          <p className="whitespace-pre-line text-sm leading-relaxed text-foreground">
            {s.approach.summary}
          </p>
        ) : null}

        {s.approach.strategy && s.approach.strategy.length > 0 ? (
          <div className="rounded-xl border border-border bg-card p-4 sm:p-5">
            <p className="mb-3 text-xs font-semibold uppercase tracking-wide text-muted-foreground">
              Strategy
            </p>
            <ol className="space-y-2.5 text-sm leading-relaxed">
              {s.approach.strategy.map((step, idx) => (
                <li key={idx} className="flex gap-3">
                  <span className="mt-0.5 inline-flex h-5 w-5 shrink-0 items-center justify-center rounded-full bg-foreground/10 font-mono text-[11px] font-semibold text-foreground">
                    {idx + 1}
                  </span>
                  <span>{step}</span>
                </li>
              ))}
            </ol>
          </div>
        ) : null}

        <div className="grid gap-3 sm:grid-cols-2">
          {s.approach.timeComplexity ? (
            <ComplexityBadge
              kind="time"
              expression={s.approach.timeComplexity}
              note={s.approach.timeComplexityNote}
            />
          ) : null}
          {s.approach.spaceComplexity ? (
            <ComplexityBadge
              kind="space"
              expression={s.approach.spaceComplexity}
              note={s.approach.spaceComplexityNote}
            />
          ) : null}
        </div>
      </section>

      {s.description ? (
        <details className="group mt-8 rounded-xl border border-border bg-card open:bg-card">
          <summary className="cursor-pointer list-none px-5 py-3 text-sm font-semibold text-foreground transition-colors hover:bg-muted/40 group-open:border-b group-open:border-border">
            <span className="inline-flex items-center gap-2">
              Problem description
              <span className="text-xs font-normal text-muted-foreground">
                (from LeetCode)
              </span>
            </span>
          </summary>
          <div className="px-5 py-4 text-sm leading-relaxed text-foreground">
            <p className="whitespace-pre-line">{s.description}</p>
          </div>
        </details>
      ) : null}

      {s.examples.length > 0 ? (
        <section className="mt-8">
          <h2 className="mb-3 text-sm font-semibold uppercase tracking-wide text-muted-foreground">
            Examples
          </h2>
          <div className="flex flex-col gap-3">
            {s.examples.map((ex, idx) => (
              <div key={idx} className="rounded-xl border border-border bg-card p-4">
                <div className="mb-2 text-xs font-semibold text-muted-foreground">
                  Example {idx + 1}
                </div>
                <dl className="space-y-1.5 font-mono text-xs leading-relaxed">
                  <div className="flex gap-2">
                    <dt className="shrink-0 text-muted-foreground">Input:</dt>
                    <dd className="text-foreground">{ex.input}</dd>
                  </div>
                  <div className="flex gap-2">
                    <dt className="shrink-0 text-muted-foreground">Output:</dt>
                    <dd className="text-foreground">{ex.output}</dd>
                  </div>
                  {ex.explanation ? (
                    <div className="flex gap-2">
                      <dt className="shrink-0 text-muted-foreground">Note:</dt>
                      <dd className="font-sans text-foreground">{ex.explanation}</dd>
                    </div>
                  ) : null}
                </dl>
              </div>
            ))}
          </div>
        </section>
      ) : null}

      {s.constraints.length > 0 ? (
        <section className="mt-8">
          <h2 className="mb-3 text-sm font-semibold uppercase tracking-wide text-muted-foreground">
            Constraints
          </h2>
          <ul className="space-y-1.5 rounded-xl border border-border bg-card p-4 font-mono text-xs leading-relaxed text-foreground">
            {s.constraints.map((c, idx) => (
              <li key={idx} className="flex gap-2">
                <span className="text-muted-foreground">•</span>
                <span>{c}</span>
              </li>
            ))}
          </ul>
        </section>
      ) : null}

      {s.followUp ? (
        <section className="mt-8 rounded-xl border border-accent/30 bg-accent/5 p-4">
          <p className="mb-1 text-xs font-semibold uppercase tracking-wide text-accent">
            Follow-up
          </p>
          <p className="text-sm leading-relaxed text-foreground">{s.followUp}</p>
        </section>
      ) : null}

      <section className="mt-10">
        <h2 className="mb-3 text-sm font-semibold uppercase tracking-wide text-muted-foreground">
          Solution
        </h2>
        <CodeBlock code={s.code} />
      </section>

      <footer className="mt-10 flex flex-wrap items-center justify-between gap-3 border-t border-border pt-6 text-xs text-muted-foreground">
        {solved ? <span>Solved on {solved}</span> : <span />}
        <a
          href={s.githubUrl}
          target="_blank"
          rel="noreferrer noopener"
          className="inline-flex items-center gap-1.5 hover:text-foreground"
        >
          <GithubIcon className="h-3 w-3" />
          {s.sourcePath}
        </a>
      </footer>
    </article>
  );
}
