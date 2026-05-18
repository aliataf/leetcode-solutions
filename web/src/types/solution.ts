export type Difficulty = "Easy" | "Medium" | "Hard";

export type Topic =
  | "arrays"
  | "backtracking"
  | "binary-search"
  | "dynamic-programming"
  | "graphs"
  | "greedy"
  | "heap"
  | "linked-lists"
  | "math"
  | "misc"
  | "sliding-window"
  | "stack-queue"
  | "strings"
  | "trees"
  | "two-pointers";

export interface Example {
  input: string;
  output: string;
  explanation?: string;
}

export interface ApproachBlock {
  title: string;
  keyInsight?: string;
  strategy?: string[];
  summary?: string;
  timeComplexity?: string;
  timeComplexityNote?: string;
  spaceComplexity?: string;
  spaceComplexityNote?: string;
}

export interface Solution {
  slug: string;
  number: number;
  paddedNumber: string;
  title: string;
  link: string;
  difficulty: Difficulty;
  topic: Topic;
  topicLabel: string;
  description: string;
  examples: Example[];
  constraints: string[];
  followUp?: string;
  approach: ApproachBlock;
  code: string;
  sourcePath: string;
  githubUrl: string;
  firstCommittedAt?: string;
  lastCommittedAt?: string;
  lineCount: number;
}

export interface SolutionsManifest {
  generatedAt: string;
  total: number;
  byDifficulty: Record<Difficulty, number>;
  byTopic: Partial<Record<Topic, number>>;
  solutions: Solution[];
}
