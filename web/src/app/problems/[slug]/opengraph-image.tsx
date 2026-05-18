import { ImageResponse } from "next/og";
import { notFound } from "next/navigation";
import { OWNER } from "@/lib/constants";
import { getAllSlugs, getSolutionBySlug } from "@/lib/solutions";

export const alt = "LeetCode solution preview";
export const size = { width: 1200, height: 630 };
export const contentType = "image/png";
export const dynamic = "force-static";

export function generateStaticParams() {
  return getAllSlugs().map((slug) => ({ slug }));
}

const DIFFICULTY_COLORS = {
  Easy: "#73d77c",
  Medium: "#f4c074",
  Hard: "#f47373",
} as const;

export default async function Image({
  params,
}: {
  params: Promise<{ slug: string }>;
}) {
  const { slug } = await params;
  const s = getSolutionBySlug(slug);
  if (!s) notFound();

  const dColor = DIFFICULTY_COLORS[s.difficulty];

  return new ImageResponse(
    (
      <div
        style={{
          width: "100%",
          height: "100%",
          display: "flex",
          flexDirection: "column",
          justifyContent: "space-between",
          padding: "72px",
          backgroundColor: "#0d0f1e",
          backgroundImage:
            "radial-gradient(circle at 10% 0%, rgba(120, 119, 198, 0.25), transparent 50%), radial-gradient(circle at 100% 100%, rgba(56, 189, 248, 0.12), transparent 55%)",
          color: "white",
          fontFamily: "sans-serif",
        }}
      >
        <div style={{ display: "flex", alignItems: "center", gap: 16 }}>
          <div
            style={{
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              width: 56,
              height: 56,
              borderRadius: 12,
              backgroundColor: "#7c89ff",
              fontFamily: "monospace",
              fontSize: 22,
              color: "#0d0f1e",
              fontWeight: 700,
            }}
          >
            {"</>"}
          </div>
          <div style={{ display: "flex", flexDirection: "column" }}>
            <span style={{ fontSize: 22, opacity: 0.7 }}>leetcode.aliataf.com</span>
            <span style={{ fontSize: 18, opacity: 0.5 }}>by {OWNER.name}</span>
          </div>
        </div>

        <div style={{ display: "flex", flexDirection: "column", gap: 18 }}>
          <div style={{ display: "flex", alignItems: "center", gap: 14 }}>
            <span
              style={{
                fontSize: 26,
                fontFamily: "monospace",
                padding: "6px 14px",
                borderRadius: 8,
                backgroundColor: "rgba(255,255,255,0.08)",
                border: "1px solid rgba(255,255,255,0.12)",
                color: "#9aa8ff",
              }}
            >
              LeetCode #{s.number}
            </span>
            <span
              style={{
                fontSize: 26,
                padding: "6px 18px",
                borderRadius: 999,
                backgroundColor: `${dColor}22`,
                border: `1px solid ${dColor}55`,
                color: dColor,
              }}
            >
              {s.difficulty}
            </span>
            <span
              style={{
                fontSize: 22,
                opacity: 0.55,
                marginLeft: 4,
              }}
            >
              · {s.topicLabel}
            </span>
          </div>
          <h1
            style={{
              fontSize: clampTitleSize(s.title),
              fontWeight: 700,
              margin: 0,
              lineHeight: 1.05,
              letterSpacing: -1.5,
              maxWidth: 1050,
            }}
          >
            {s.title}
          </h1>
          {s.approach.title ? (
            <p
              style={{
                fontSize: 28,
                opacity: 0.75,
                margin: 0,
                marginTop: 4,
                maxWidth: 1000,
              }}
            >
              Approach: {s.approach.title}
            </p>
          ) : null}
        </div>

        <div
          style={{
            display: "flex",
            alignItems: "center",
            justifyContent: "space-between",
            fontSize: 22,
            opacity: 0.7,
          }}
        >
          <span style={{ fontFamily: "monospace" }}>
            {s.approach.timeComplexity ? `time ${s.approach.timeComplexity}` : ""}
            {s.approach.timeComplexity && s.approach.spaceComplexity ? "    " : ""}
            {s.approach.spaceComplexity ? `space ${s.approach.spaceComplexity}` : ""}
          </span>
          <span>C++ Solution</span>
        </div>
      </div>
    ),
    size,
  );
}

function clampTitleSize(title: string): number {
  if (title.length > 48) return 64;
  if (title.length > 32) return 76;
  return 92;
}
