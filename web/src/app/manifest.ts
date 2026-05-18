import type { MetadataRoute } from "next";
import { OWNER } from "@/lib/constants";

export const dynamic = "force-static";

export default function manifest(): MetadataRoute.Manifest {
  return {
    name: `${OWNER.name} — LeetCode Solutions in C++`,
    short_name: "LeetCode Solutions",
    description:
      "Worked-out LeetCode solutions in modern C++ — approach, complexity, and clean source for every problem.",
    start_url: "/",
    display: "standalone",
    background_color: "#0d0f1e",
    theme_color: "#15172a",
    categories: ["education", "developer", "productivity"],
    lang: "en-US",
    orientation: "any",
    icons: [
      {
        src: "/favicon.ico",
        sizes: "any",
        type: "image/x-icon",
      },
    ],
  };
}
