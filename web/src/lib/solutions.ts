import manifest from "@/data/solutions.json";
import type { Solution, SolutionsManifest } from "@/types/solution";

const data = manifest as unknown as SolutionsManifest;

export function getManifest(): SolutionsManifest {
  return data;
}

export function getAllSolutions(): Solution[] {
  return data.solutions;
}

export function getSolutionBySlug(slug: string): Solution | undefined {
  return data.solutions.find((s) => s.slug === slug);
}

export function getAllSlugs(): string[] {
  return data.solutions.map((s) => s.slug);
}
