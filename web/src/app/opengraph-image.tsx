import { ImageResponse } from "next/og";
import { OWNER } from "@/lib/constants";
import { getManifest } from "@/lib/solutions";

export const alt = `${OWNER.name} — LeetCode Solutions in C++`;
export const size = { width: 1200, height: 630 };
export const contentType = "image/png";
export const dynamic = "force-static";

export default function Image() {
  const { total, byDifficulty } = getManifest();

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
            "radial-gradient(circle at 20% 0%, rgba(120, 119, 198, 0.25), transparent 50%), radial-gradient(circle at 100% 100%, rgba(56, 189, 248, 0.15), transparent 50%)",
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

        <div style={{ display: "flex", flexDirection: "column", gap: 12 }}>
          <span style={{ fontSize: 28, color: "#9aa8ff", letterSpacing: 4 }}>
            LEETCODE · C++
          </span>
          <h1
            style={{
              fontSize: 92,
              fontWeight: 700,
              margin: 0,
              lineHeight: 1.05,
              letterSpacing: -2,
            }}
          >
            {total} solutions
            <br />
            <span style={{ color: "#9aa8ff" }}>worked out in depth</span>
          </h1>
          <p style={{ fontSize: 28, opacity: 0.75, margin: 0, marginTop: 8 }}>
            Approach, complexity, and clean source for every problem.
          </p>
        </div>

        <div style={{ display: "flex", gap: 16, fontSize: 22 }}>
          <Pill color="#73d77c">{byDifficulty.Easy} Easy</Pill>
          <Pill color="#f4c074">{byDifficulty.Medium} Medium</Pill>
          <Pill color="#f47373">{byDifficulty.Hard} Hard</Pill>
        </div>
      </div>
    ),
    size,
  );
}

function Pill({ color, children }: { color: string; children: React.ReactNode }) {
  return (
    <div
      style={{
        display: "flex",
        alignItems: "center",
        gap: 10,
        padding: "10px 20px",
        borderRadius: 999,
        backgroundColor: "rgba(255,255,255,0.06)",
        border: "1px solid rgba(255,255,255,0.12)",
      }}
    >
      <div
        style={{
          width: 12,
          height: 12,
          borderRadius: 999,
          backgroundColor: color,
        }}
      />
      <span style={{ opacity: 0.92 }}>{children}</span>
    </div>
  );
}
