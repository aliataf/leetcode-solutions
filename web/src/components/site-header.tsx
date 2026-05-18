import Link from "next/link";
import { ThemeToggle } from "@/components/theme-toggle";
import { GithubIcon } from "@/components/icons";
import { OWNER } from "@/lib/constants";

export function SiteHeader() {
  return (
    <header className="sticky top-0 z-40 w-full border-b border-border bg-background/85 backdrop-blur supports-backdrop-filter:bg-background/65">
      <div className="mx-auto flex h-14 max-w-6xl items-center gap-6 px-4 sm:px-6">
        <Link href="/" className="group flex items-center gap-2 text-sm font-semibold tracking-tight">
          <span className="inline-flex h-7 w-7 items-center justify-center rounded-md bg-accent text-accent-foreground transition-transform group-hover:scale-105">
            <span className="font-mono text-[11px] leading-none">{"</>"}</span>
          </span>
          <span>
            {OWNER.name.split(" ")[0]}
            <span className="text-muted-foreground"> · LeetCode</span>
          </span>
        </Link>
        <nav className="ml-auto flex items-center gap-1 sm:gap-2 text-sm">
          <Link
            href="/problems"
            className="rounded-md px-3 py-1.5 text-muted-foreground transition-colors hover:bg-muted hover:text-foreground"
          >
            Problems
          </Link>
          <Link
            href="/about"
            className="rounded-md px-3 py-1.5 text-muted-foreground transition-colors hover:bg-muted hover:text-foreground"
          >
            About
          </Link>
          <a
            href={OWNER.repo}
            target="_blank"
            rel="noreferrer noopener"
            aria-label="GitHub repository"
            className="inline-flex h-9 w-9 items-center justify-center rounded-md text-muted-foreground transition-colors hover:bg-muted hover:text-foreground"
          >
            <GithubIcon className="h-4 w-4" />
          </a>
          <ThemeToggle />
        </nav>
      </div>
    </header>
  );
}
