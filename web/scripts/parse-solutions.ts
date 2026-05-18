import { execFileSync } from "node:child_process";
import { readFileSync, readdirSync, statSync, writeFileSync, mkdirSync } from "node:fs";
import { dirname, join, resolve } from "node:path";
import { fileURLToPath } from "node:url";

import type {
  ApproachBlock,
  Difficulty,
  Example,
  Solution,
  SolutionsManifest,
  Topic,
} from "../src/types/solution";
import { TOPIC_LABELS, OWNER } from "../src/lib/constants";
import { filenameToSlug } from "../src/lib/slug";

const __dirname = dirname(fileURLToPath(import.meta.url));
const REPO_ROOT = resolve(__dirname, "..", "..");
const OUT_FILE = resolve(__dirname, "..", "src", "data", "solutions.json");

const KNOWN_TOPICS = Object.keys(TOPIC_LABELS) as Topic[];
const FILE_RE = /^\d{4}_.+\.cpp$/;

function readUtf8(path: string) {
  return readFileSync(path, "utf8").replace(/\r\n/g, "\n");
}

function stripCommentStars(block: string) {
  return block
    .split("\n")
    .map((l) =>
      l
        .replace(/^\s*\/\*+\s?/, "")
        .replace(/\s*\*\/\s*$/, "")
        .replace(/^\s*\*\s?/, ""),
    )
    .join("\n")
    .trim();
}

interface SectionMatch {
  label: string;
  start: number;
  end: number;
  body: string;
}

function sliceSections(text: string, labels: string[]): Map<string, string> {
  const found: SectionMatch[] = [];
  for (const label of labels) {
    const escaped = label.replace(/[.*+?^${}()|[\]\\]/g, "\\$&");
    // Match either at line start OR after a sentence-ending punctuation + space.
    // The second form handles wrapped comments where a section label gets
    // folded into the previous paragraph (e.g. "...for pointers. Space Complexity: ...").
    const re = new RegExp(`(?:^|[.!?\\s])\\s*${escaped}\\s*`, "m");
    const m = re.exec(text);
    if (m) {
      // Position the start at the label itself, not the preceding whitespace.
      const labelStart = m.index + m[0].indexOf(label);
      found.push({
        label,
        start: labelStart,
        end: labelStart + label.length,
        body: "",
      });
    }
  }
  found.sort((a, b) => a.start - b.start);
  for (let i = 0; i < found.length; i++) {
    const next = found[i + 1];
    found[i].body = text
      .slice(found[i].end, next ? next.start : text.length)
      .trim();
  }
  const out = new Map<string, string>();
  for (const s of found) out.set(s.label, s.body);
  return out;
}

function parseExamples(text: string): Example[] {
  if (!text) return [];
  const blocks: string[] = [];
  const lines = text.split("\n");
  let buf: string[] = [];
  const headingRe = /^Example(?:\s*\d+)?:\s*$/;
  for (const line of lines) {
    if (headingRe.test(line.trim())) {
      if (buf.length) {
        blocks.push(buf.join("\n").trim());
        buf = [];
      }
      continue;
    }
    buf.push(line);
  }
  if (buf.length) blocks.push(buf.join("\n").trim());

  const out: Example[] = [];
  for (const raw of blocks) {
    if (!raw) continue;
    const inputMatch = raw.match(/^Input:\s*([\s\S]*?)(?=\n(?:Output:|Explanation:)|$)/m);
    const outputMatch = raw.match(/^Output:\s*([\s\S]*?)(?=\n(?:Explanation:)|$)/m);
    const explanationMatch = raw.match(/^Explanation:\s*([\s\S]*)$/m);
    if (!inputMatch && !outputMatch) continue;
    out.push({
      input: inputMatch?.[1].trim() ?? "",
      output: outputMatch?.[1].trim() ?? "",
      explanation: explanationMatch?.[1].trim() || undefined,
    });
  }
  return out;
}

function parseConstraints(text: string): string[] {
  if (!text) return [];
  const lines = text.split("\n").map((l) => l.trim());
  const out: string[] = [];
  for (const line of lines) {
    if (!line) continue;
    if (line.startsWith("- ")) out.push(line.slice(2).trim());
    else if (out.length > 0) {
      out[out.length - 1] += " " + line;
    }
  }
  return out;
}

interface HeaderData {
  number: number;
  title: string;
  link: string;
  difficulty: Difficulty;
  description: string;
  examples: Example[];
  constraints: string[];
  followUp?: string;
}

function parseHeader(source: string): HeaderData {
  const blockMatch = source.match(/\/\*([\s\S]*?)\*\//);
  if (!blockMatch) throw new Error("Missing header comment block");
  const block = stripCommentStars(blockMatch[0]);

  const metaMatch = block.match(
    /^Problem:\s*(\d+)\.\s+(.+?)\nLink:\s*(\S+)\nDifficulty:\s*(Easy|Medium|Hard)/s,
  );
  if (!metaMatch) throw new Error("Header missing Problem/Link/Difficulty fields");

  const number = Number(metaMatch[1]);
  const title = metaMatch[2].trim();
  const link = metaMatch[3].trim();
  const difficulty = metaMatch[4] as Difficulty;

  const afterMeta = block.slice(metaMatch[0].length).trim();
  const sections = sliceSections(afterMeta, [
    "Description:",
    "Constraints:",
    "Follow up:",
    "Follow-up:",
  ]);

  // Examples (one or many) live between Description: and Constraints:
  const examplesStart = afterMeta.search(/^Example(?:\s*\d+)?:\s*$/m);
  const constraintsStart = afterMeta.search(/^Constraints:\s*\n?/m);
  let descriptionBody = sections.get("Description:") ?? "";
  let examplesBody = "";
  if (examplesStart >= 0) {
    const examplesEnd = constraintsStart >= 0 ? constraintsStart : afterMeta.length;
    examplesBody = afterMeta.slice(examplesStart, examplesEnd).trim();
    // Trim the Examples section out of the description if the section slicer pulled it in.
    descriptionBody = descriptionBody
      .replace(/\nExample(?:\s*\d+)?:[\s\S]*$/m, "")
      .trim();
  }

  const followUp =
    sections.get("Follow up:") ?? sections.get("Follow-up:") ?? undefined;

  return {
    number,
    title,
    link,
    difficulty,
    description: normalizeProse(descriptionBody),
    examples: parseExamples(examplesBody),
    constraints: parseConstraints(sections.get("Constraints:") ?? ""),
    followUp: followUp ? normalizeProse(followUp) : undefined,
  };
}

function normalizeProse(s: string) {
  return s
    .split(/\n{2,}/)
    .map((para) => para.split("\n").map((l) => l.trim()).join(" ").trim())
    .filter(Boolean)
    .join("\n\n");
}

function parseApproach(classBody: string): ApproachBlock {
  const docMatch = classBody.match(/\/\*([\s\S]*?)\*\//);
  if (!docMatch) throw new Error("Missing approach doc block inside Solution");
  const doc = stripCommentStars(docMatch[0]);

  const approachMatch = doc.match(/^Approach(?:\s*\d+)?:\s*(.+?)(?:\n|$)/);
  if (!approachMatch) throw new Error("Missing 'Approach:' line");
  const title = approachMatch[1].trim();

  const rest = doc.slice(approachMatch[0].length).trim();
  const sections = sliceSections(rest, [
    "Key Insight:",
    "Strategy:",
    "Time Complexity:",
    "Space Complexity:",
  ]);

  const keyInsightRaw = sections.get("Key Insight:");
  const strategyRaw = sections.get("Strategy:");
  const timeRaw = sections.get("Time Complexity:");
  const spaceRaw = sections.get("Space Complexity:");

  // Anything before the first known label is the free-form summary.
  let summaryEnd = rest.length;
  for (const label of ["Key Insight:", "Strategy:", "Time Complexity:", "Space Complexity:"]) {
    const idx = rest.search(new RegExp(`^${label.replace(/:/, ":")}`, "m"));
    if (idx >= 0 && idx < summaryEnd) summaryEnd = idx;
  }
  const summaryRaw = rest.slice(0, summaryEnd).trim();

  const summary = summaryRaw ? normalizeProse(summaryRaw) : undefined;
  const fallback = extractInlineComplexity(summary ?? "");

  const timeCx = timeRaw ? splitComplexity("time", timeRaw) : fallback.time;
  const spaceCx = spaceRaw ? splitComplexity("space", spaceRaw) : fallback.space;

  return {
    title,
    keyInsight: keyInsightRaw ? normalizeProse(keyInsightRaw) : undefined,
    strategy: strategyRaw ? parseStrategy(strategyRaw) : undefined,
    summary,
    ...timeCx,
    ...spaceCx,
  };
}

function extractInlineComplexity(text: string): {
  time: Partial<ApproachBlock>;
  space: Partial<ApproachBlock>;
} {
  const out: { time: Partial<ApproachBlock>; space: Partial<ApproachBlock> } = {
    time: {},
    space: {},
  };
  if (!text) return out;
  const timeMatch = text.match(/O\([^)]+\)\s*(?:time|runtime)\b/i);
  if (timeMatch) {
    out.time.timeComplexity = timeMatch[0].replace(/\s*(?:time|runtime)\b/i, "").trim();
  }
  const spaceMatch = text.match(/O\([^)]+\)\s*(?:extra\s+)?(?:space|memory|auxiliary)\b/i);
  if (spaceMatch) {
    out.space.spaceComplexity = spaceMatch[0]
      .replace(/\s*(?:extra\s+)?(?:space|memory|auxiliary)\b/i, "")
      .trim();
  }
  return out;
}

function parseStrategy(text: string): string[] {
  const trimmed = text.trim();
  const steps: string[] = [];
  const re = /^(\d+)\.\s+([\s\S]*?)(?=\n\d+\.\s+|$)/gm;
  let m: RegExpExecArray | null;
  while ((m = re.exec(trimmed)) !== null) {
    steps.push(m[2].trim().replace(/\s+/g, " "));
  }
  return steps;
}

function splitComplexity(
  kind: "time" | "space",
  raw: string,
): Partial<ApproachBlock> {
  const trimmed = raw.replace(/\s+/g, " ").trim();
  const { expr, note } = extractBigO(trimmed);
  if (kind === "time") {
    return {
      timeComplexity: expr || trimmed,
      timeComplexityNote: note || undefined,
    };
  }
  return {
    spaceComplexity: expr || trimmed,
    spaceComplexityNote: note || undefined,
  };
}

function extractBigO(text: string): { expr: string; note: string } {
  // Find one or more O(...) expressions chained by "or"/"+"/"*"/"/" and
  // separate them from any trailing description.
  const exprRe = /O\(([^()]*(?:\([^()]*\)[^()]*)*)\)/g;
  const matches: { idx: number; end: number; str: string }[] = [];
  let m: RegExpExecArray | null;
  while ((m = exprRe.exec(text)) !== null) {
    matches.push({ idx: m.index, end: m.index + m[0].length, str: m[0] });
  }
  if (matches.length === 0) return { expr: "", note: text.trim() };

  let end = matches[0].end;
  let i = 1;
  while (i < matches.length) {
    const between = text.slice(end, matches[i].idx).trim();
    if (/^(or|\+|\*|\/|,)\s*$/i.test(between)) {
      end = matches[i].end;
      i++;
    } else {
      break;
    }
  }
  const expr = text.slice(matches[0].idx, end).trim();
  let note = text.slice(end).trim();
  note = note.replace(/^[-—,.\s]+/, "").replace(/^(?:where|for|depending|when|because|since|due\s+to|with)\s+/i, "");
  return { expr, note: note.trim() };
}

function extractCode(source: string): string {
  const supportingStructs: string[] = [];
  const structRe = /^\s*(struct\s+\w+\s*\{[\s\S]*?^\};)/gm;
  let sm: RegExpExecArray | null;
  while ((sm = structRe.exec(source)) !== null) {
    supportingStructs.push(sm[1].trim());
  }

  const classMatch = source.match(/^(class\s+Solution\s*\{[\s\S]*?\n\};)/m);
  if (!classMatch) throw new Error("Missing 'class Solution { ... };' block");
  let classBody = classMatch[1];
  // Remove the leading approach doc comment.
  classBody = classBody.replace(/\s*\/\*[\s\S]*?\*\/\s*\n?/, "\n");
  classBody = classBody.replace(/^class Solution \{\s*\n/, "class Solution {\n");

  const parts = [...supportingStructs, classBody.trim()];
  return parts.join("\n\n");
}

function getClassBody(source: string): string {
  const classMatch = source.match(/^(class\s+Solution\s*\{[\s\S]*?\n\};)/m);
  if (!classMatch) throw new Error("Missing 'class Solution' block");
  return classMatch[1];
}

interface GitDates {
  firstCommittedAt?: string;
  lastCommittedAt?: string;
}

function gitDates(repoRelPath: string): GitDates {
  try {
    const firstOut = execFileSync(
      "git",
      ["log", "--diff-filter=A", "--follow", "--format=%aI", "--", repoRelPath],
      { cwd: REPO_ROOT, encoding: "utf8" },
    ).trim();
    const lastOut = execFileSync(
      "git",
      ["log", "-1", "--format=%aI", "--", repoRelPath],
      { cwd: REPO_ROOT, encoding: "utf8" },
    ).trim();
    const firstLines = firstOut.split("\n").filter(Boolean);
    return {
      firstCommittedAt: firstLines.length ? firstLines[firstLines.length - 1] : undefined,
      lastCommittedAt: lastOut || undefined,
    };
  } catch {
    return {};
  }
}

function parseSolutionFile(topic: Topic, filename: string): Solution {
  const repoRelPath = `${topic}/${filename}`;
  const absPath = join(REPO_ROOT, repoRelPath);
  const source = readUtf8(absPath);
  const header = parseHeader(source);
  const classBody = getClassBody(source);
  const approach = parseApproach(classBody);
  const code = extractCode(source);
  const dates = gitDates(repoRelPath);

  const slug = filenameToSlug(filename);
  return {
    slug,
    number: header.number,
    paddedNumber: filename.slice(0, 4),
    title: header.title,
    link: header.link,
    difficulty: header.difficulty,
    topic,
    topicLabel: TOPIC_LABELS[topic],
    description: header.description,
    examples: header.examples,
    constraints: header.constraints,
    followUp: header.followUp,
    approach,
    code,
    sourcePath: repoRelPath,
    githubUrl: `${OWNER.repoBlobBase}/${repoRelPath}`,
    firstCommittedAt: dates.firstCommittedAt,
    lastCommittedAt: dates.lastCommittedAt,
    lineCount: source.split("\n").length,
  };
}

function main() {
  const solutions: Solution[] = [];
  for (const topic of KNOWN_TOPICS) {
    const topicDir = join(REPO_ROOT, topic);
    let entries: string[];
    try {
      entries = readdirSync(topicDir);
    } catch {
      continue;
    }
    for (const filename of entries) {
      if (!FILE_RE.test(filename)) continue;
      if (filename === "TEMPLATE.cpp") continue;
      const full = join(topicDir, filename);
      if (!statSync(full).isFile()) continue;
      try {
        solutions.push(parseSolutionFile(topic, filename));
      } catch (err) {
        console.error(`[parse-solutions] Failed to parse ${topic}/${filename}: ${(err as Error).message}`);
        throw err;
      }
    }
  }

  solutions.sort((a, b) => a.number - b.number || a.title.localeCompare(b.title));

  const byDifficulty: Record<Difficulty, number> = { Easy: 0, Medium: 0, Hard: 0 };
  const byTopic: Partial<Record<Topic, number>> = {};
  for (const s of solutions) {
    byDifficulty[s.difficulty] += 1;
    byTopic[s.topic] = (byTopic[s.topic] ?? 0) + 1;
  }

  const manifest: SolutionsManifest = {
    generatedAt: new Date().toISOString(),
    total: solutions.length,
    byDifficulty,
    byTopic,
    solutions,
  };

  mkdirSync(dirname(OUT_FILE), { recursive: true });
  writeFileSync(OUT_FILE, JSON.stringify(manifest, null, 2) + "\n", "utf8");
  console.log(
    `[parse-solutions] Wrote ${solutions.length} solutions → ${OUT_FILE}`,
  );
  console.log(
    `  Easy: ${byDifficulty.Easy} · Medium: ${byDifficulty.Medium} · Hard: ${byDifficulty.Hard}`,
  );
}

main();
