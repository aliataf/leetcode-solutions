import type { Topic } from "@/types/solution";

export const SITE_URL =
  process.env.NEXT_PUBLIC_SITE_URL ?? "https://leetcode.aliataf.com";

export const OWNER = {
  name: "Ali Ataf",
  email: "ali@aliataf.com",
  github: "https://github.com/aliataf",
  leetcode: "https://leetcode.com/u/aliataf",
  portfolio: "https://aliataf.com",
  repo: "https://github.com/aliataf/leetcode-solutions",
  repoBlobBase: "https://github.com/aliataf/leetcode-solutions/blob/main",
} as const;

export const TOPIC_LABELS: Record<Topic, string> = {
  arrays: "Arrays",
  backtracking: "Backtracking",
  "binary-search": "Binary Search",
  "dynamic-programming": "Dynamic Programming",
  graphs: "Graphs",
  greedy: "Greedy",
  heap: "Heap",
  "linked-lists": "Linked Lists",
  math: "Math",
  misc: "Misc",
  "sliding-window": "Sliding Window",
  "stack-queue": "Stack & Queue",
  strings: "Strings",
  trees: "Trees",
  "two-pointers": "Two Pointers",
};

export const TOPIC_ORDER: Topic[] = [
  "arrays",
  "strings",
  "linked-lists",
  "trees",
  "graphs",
  "dynamic-programming",
  "math",
  "two-pointers",
  "sliding-window",
  "binary-search",
  "stack-queue",
  "greedy",
  "backtracking",
  "heap",
  "misc",
];

export const FEATURED_SLUGS = [
  "0042-trapping-rain-water",
  "0023-merge-k-sorted-lists",
  "0076-minimum-window-substring",
];
