import Link from "next/link";
import { OWNER } from "@/lib/constants";

export function SiteFooter() {
  return (
    <footer className="border-t border-border bg-background">
      <div className="mx-auto flex max-w-6xl flex-col gap-3 px-4 py-6 text-xs text-muted-foreground sm:flex-row sm:items-center sm:justify-between sm:px-6">
        <p>
          Built by{" "}
          <a
            href={OWNER.github}
            target="_blank"
            rel="noreferrer noopener"
            className="font-medium text-foreground hover:text-accent"
          >
            {OWNER.name}
          </a>
          . Solutions parsed from the{" "}
          <a
            href={OWNER.repo}
            target="_blank"
            rel="noreferrer noopener"
            className="font-medium text-foreground hover:text-accent"
          >
            source repo
          </a>
          .
        </p>
        <div className="flex items-center gap-4">
          <Link href="/problems" className="hover:text-foreground">
            Problems
          </Link>
          <Link href="/about" className="hover:text-foreground">
            About
          </Link>
          <a href={`mailto:${OWNER.email}`} className="hover:text-foreground">
            {OWNER.email}
          </a>
        </div>
      </div>
    </footer>
  );
}
