import { renderCpp } from "@/lib/shiki";
import { CopyButton } from "@/components/copy-button";

export async function CodeBlock({ code }: { code: string }) {
  const html = await renderCpp(code);
  return (
    <div className="group relative overflow-hidden rounded-xl border border-border bg-card">
      <div className="flex items-center justify-between border-b border-border px-3 py-1.5 text-xs text-muted-foreground">
        <span className="font-mono">solution.cpp</span>
        <CopyButton text={code} />
      </div>
      <div
        className="overflow-x-auto px-4 py-4 text-sm"
        dangerouslySetInnerHTML={{ __html: html }}
      />
    </div>
  );
}
