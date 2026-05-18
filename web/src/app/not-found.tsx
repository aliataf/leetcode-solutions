import Link from "next/link";

export default function NotFound() {
  return (
    <div className="mx-auto flex max-w-2xl flex-col items-center gap-4 px-4 py-24 text-center">
      <p className="font-mono text-xs text-muted-foreground">404</p>
      <h1 className="text-3xl font-semibold tracking-tight">Not found</h1>
      <p className="text-sm text-muted-foreground">
        That page doesn&apos;t exist. Maybe browse the problems instead.
      </p>
      <Link
        href="/problems"
        className="mt-4 inline-flex h-9 items-center rounded-md bg-foreground px-4 text-sm font-medium text-background transition-opacity hover:opacity-90"
      >
        View problems
      </Link>
    </div>
  );
}
