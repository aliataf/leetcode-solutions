import { Suspense } from "react";
import type { Metadata } from "next";
import { ProblemTable } from "@/components/problems/problem-table";
import { getAllSolutions, getManifest } from "@/lib/solutions";

export const metadata: Metadata = {
  title: "All LeetCode Solutions in C++",
  description:
    "Browse every solved LeetCode problem with C++ source, approach, and time/space complexity. Filter by topic or difficulty, search by problem number or title.",
  alternates: { canonical: "/problems" },
  openGraph: {
    title: "All LeetCode Solutions in C++",
    description:
      "Browse every solved LeetCode problem with C++ source, approach, and time/space complexity.",
    url: "/problems",
    type: "website",
  },
  twitter: {
    card: "summary_large_image",
    title: "All LeetCode Solutions in C++",
    description:
      "Browse every solved LeetCode problem with C++ source, approach, and time/space complexity.",
  },
};

export default function ProblemsPage() {
  const solutions = getAllSolutions();
  const { total, byDifficulty } = getManifest();

  return (
    <div className="mx-auto max-w-6xl px-4 py-10 sm:px-6 sm:py-12">
      <header className="mb-6 flex flex-col gap-2">
        <h1 className="text-3xl font-semibold tracking-tight">
          All LeetCode Solutions in C++
        </h1>
        <p className="text-sm text-muted-foreground">
          {total} problems solved · {byDifficulty.Easy} Easy ·{" "}
          {byDifficulty.Medium} Medium · {byDifficulty.Hard} Hard. Search,
          filter by topic or difficulty, sort by recency.
        </p>
      </header>
      <Suspense fallback={<div className="text-sm text-muted-foreground">Loading…</div>}>
        <ProblemTable solutions={solutions} />
      </Suspense>
    </div>
  );
}
