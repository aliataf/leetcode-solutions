import type { Metadata } from "next";
import { Code2, Globe, Mail } from "lucide-react";
import { GithubIcon } from "@/components/icons";
import { OWNER } from "@/lib/constants";

export const metadata: Metadata = {
  title: `About ${OWNER.name}`,
  description: `${OWNER.name} — software engineer. Background, skills, and the LeetCode solutions notebook behind this site.`,
  alternates: { canonical: "/about" },
  openGraph: {
    title: `About ${OWNER.name}`,
    description: `${OWNER.name} — software engineer. Background, skills, and the LeetCode solutions notebook behind this site.`,
    url: "/about",
    type: "profile",
  },
};

const skills = [
  "C++",
  "TypeScript",
  "React",
  "Next.js",
  "Node.js",
  "PostgreSQL",
  "Algorithms & data structures",
  "System design",
];

export default function AboutPage() {
  return (
    <div className="mx-auto max-w-2xl px-4 py-12 sm:px-6 sm:py-16">
      <h1 className="text-3xl font-semibold tracking-tight sm:text-4xl">About</h1>
      <p className="mt-4 text-base leading-relaxed text-foreground">
        I&apos;m {OWNER.name}, a software engineer who likes building backend
        systems and clean web apps. This site is a working notebook of LeetCode
        problems I&apos;ve solved in C++ — each one with the approach written
        out, complexity analysis, and the actual code, all so anyone (myself
        included) can read back the reasoning later.
      </p>

      <section className="mt-8">
        <h2 className="text-xs font-semibold uppercase tracking-wider text-muted-foreground">
          Skills
        </h2>
        <ul className="mt-3 flex flex-wrap gap-2">
          {skills.map((skill) => (
            <li
              key={skill}
              className="rounded-md border border-border bg-card px-2.5 py-1 text-xs text-foreground"
            >
              {skill}
            </li>
          ))}
        </ul>
      </section>

      <section className="mt-8">
        <h2 className="text-xs font-semibold uppercase tracking-wider text-muted-foreground">
          Links
        </h2>
        <ul className="mt-3 flex flex-col gap-2 text-sm">
          <li>
            <a
              href={OWNER.portfolio}
              target="_blank"
              rel="noreferrer noopener"
              className="inline-flex items-center gap-2 text-foreground transition-colors hover:text-accent"
            >
              <Globe className="h-4 w-4" />
              aliataf.com
            </a>
          </li>
          <li>
            <a
              href={OWNER.github}
              target="_blank"
              rel="noreferrer noopener"
              className="inline-flex items-center gap-2 text-foreground transition-colors hover:text-accent"
            >
              <GithubIcon className="h-4 w-4" />
              github.com/aliataf
            </a>
          </li>
          <li>
            <a
              href={OWNER.leetcode}
              target="_blank"
              rel="noreferrer noopener"
              className="inline-flex items-center gap-2 text-foreground transition-colors hover:text-accent"
            >
              <Code2 className="h-4 w-4" />
              leetcode.com/u/aliataf
            </a>
          </li>
          <li>
            <a
              href={`mailto:${OWNER.email}`}
              className="inline-flex items-center gap-2 text-foreground transition-colors hover:text-accent"
            >
              <Mail className="h-4 w-4" />
              {OWNER.email}
            </a>
          </li>
        </ul>
      </section>

      <section className="mt-12 rounded-xl border border-border bg-card p-5 text-sm leading-relaxed text-muted-foreground">
        <h2 className="mb-2 text-sm font-semibold text-foreground">
          About this site
        </h2>
        <p>
          Built with Next.js, TypeScript, Tailwind CSS, and{" "}
          <a
            href="https://shiki.style"
            target="_blank"
            rel="noreferrer noopener"
            className="text-foreground hover:text-accent"
          >
            shiki
          </a>{" "}
          for syntax highlighting. Solutions are parsed directly from the
          source repo at build time — no manual curation, no analytics, no
          backend. The whole thing is a static export deployed to Vercel.
        </p>
      </section>
    </div>
  );
}
