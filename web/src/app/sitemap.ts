import type { MetadataRoute } from "next";
import { getAllSolutions } from "@/lib/solutions";
import { SITE_URL } from "@/lib/constants";

export const dynamic = "force-static";

export default function sitemap(): MetadataRoute.Sitemap {
  const now = new Date();
  const solutions = getAllSolutions();
  const mostRecent = solutions
    .map((s) => s.lastCommittedAt ?? s.firstCommittedAt)
    .filter((d): d is string => Boolean(d))
    .sort()
    .at(-1);
  const indexLastModified = mostRecent ? new Date(mostRecent) : now;

  const staticUrls: MetadataRoute.Sitemap = [
    {
      url: `${SITE_URL}/`,
      lastModified: indexLastModified,
      changeFrequency: "weekly",
      priority: 1.0,
    },
    {
      url: `${SITE_URL}/problems/`,
      lastModified: indexLastModified,
      changeFrequency: "weekly",
      priority: 0.9,
    },
    {
      url: `${SITE_URL}/about/`,
      lastModified: now,
      changeFrequency: "monthly",
      priority: 0.4,
    },
  ];

  // Difficulty-by-difficulty: prioritize Hard slightly higher (less competition, longer dwell).
  const difficultyPriority = { Easy: 0.65, Medium: 0.7, Hard: 0.75 } as const;
  const problemUrls: MetadataRoute.Sitemap = solutions.map((s) => ({
    url: `${SITE_URL}/problems/${s.slug}/`,
    lastModified: s.lastCommittedAt
      ? new Date(s.lastCommittedAt)
      : s.firstCommittedAt
        ? new Date(s.firstCommittedAt)
        : now,
    changeFrequency: "monthly",
    priority: difficultyPriority[s.difficulty],
  }));

  return [...staticUrls, ...problemUrls];
}
