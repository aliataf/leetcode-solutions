import { Suspense } from "react";
import type { Metadata } from "next";
import { ProblemTable } from "@/components/problems/problem-table";
import { getAllSolutions } from "@/lib/solutions";

export const metadata: Metadata = {
  title: "Problems",
  description: "Filterable index of every solved LeetCode problem.",
};

export default function ProblemsPage() {
  const solutions = getAllSolutions();

  return (
    <div className="mx-auto max-w-6xl px-4 py-10 sm:px-6 sm:py-12">
      <header className="mb-6 flex flex-col gap-2">
        <h1 className="text-3xl font-semibold tracking-tight">All problems</h1>
        <p className="text-sm text-muted-foreground">
          Search, filter by difficulty or topic, sort by recency. Each row links
          to the worked-out solution.
        </p>
      </header>
      <Suspense fallback={<div className="text-sm text-muted-foreground">Loading…</div>}>
        <ProblemTable solutions={solutions} />
      </Suspense>
    </div>
  );
}
