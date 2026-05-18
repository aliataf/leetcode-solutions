import { createHighlighter, type Highlighter } from "shiki";

let highlighterPromise: Promise<Highlighter> | null = null;

export function getHighlighter(): Promise<Highlighter> {
  if (!highlighterPromise) {
    highlighterPromise = createHighlighter({
      langs: ["cpp"],
      themes: ["catppuccin-latte", "catppuccin-mocha"],
    });
  }
  return highlighterPromise;
}

export async function renderCpp(code: string): Promise<string> {
  const hl = await getHighlighter();
  return hl.codeToHtml(code, {
    lang: "cpp",
    themes: {
      light: "catppuccin-latte",
      dark: "catppuccin-mocha",
    },
    defaultColor: false,
  });
}
