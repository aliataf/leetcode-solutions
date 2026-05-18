import type { MetadataRoute } from "next";
import { getAllSolutions } from "@/lib/solutions";
import { SITE_URL } from "@/lib/constants";

export const dynamic = "force-static";

export default function sitemap(): MetadataRoute.Sitemap {
  const now = new Date();
  const solutions = getAllSolutions();
  const staticUrls: MetadataRoute.Sitemap = [
    { url: `${SITE_URL}/`, lastModified: now, changeFrequency: "weekly", priority: 1 },
    { url: `${SITE_URL}/problems`, lastModified: now, changeFrequency: "weekly", priority: 0.9 },
    { url: `${SITE_URL}/about`, lastModified: now, changeFrequency: "monthly", priority: 0.5 },
  ];
  const problemUrls: MetadataRoute.Sitemap = solutions.map((s) => ({
    url: `${SITE_URL}/problems/${s.slug}`,
    lastModified: s.lastCommittedAt ? new Date(s.lastCommittedAt) : now,
    changeFrequency: "yearly",
    priority: 0.6,
  }));
  return [...staticUrls, ...problemUrls];
}
