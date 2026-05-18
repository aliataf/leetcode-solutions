import type { Metadata } from "next";
import type { Solution } from "@/types/solution";
import { OWNER, SITE_URL } from "@/lib/constants";

/**
 * Trim a prose blob into a clean meta description (search snippets show
 * roughly 150-160 chars, so we target ~155 and avoid cutting mid-word).
 */
export function truncateDescription(text: string, max = 155): string {
  const clean = text.replace(/\s+/g, " ").trim();
  if (clean.length <= max) return clean;
  const sliced = clean.slice(0, max - 1);
  const lastSpace = sliced.lastIndexOf(" ");
  return (lastSpace > 80 ? sliced.slice(0, lastSpace) : sliced).trimEnd() + "…";
}

export function absoluteUrl(path: string): string {
  return new URL(path, SITE_URL).toString();
}

const PERSON_LD = {
  "@type": "Person",
  "@id": `${SITE_URL}/#person`,
  name: OWNER.name,
  url: OWNER.portfolio,
  email: `mailto:${OWNER.email}`,
  sameAs: [OWNER.github, OWNER.leetcode, OWNER.portfolio],
};

export function websiteJsonLd() {
  return {
    "@context": "https://schema.org",
    "@graph": [
      {
        "@type": "WebSite",
        "@id": `${SITE_URL}/#website`,
        url: SITE_URL,
        name: `${OWNER.name} — LeetCode Solutions`,
        description:
          "Worked-out C++ solutions to LeetCode problems with approach, complexity analysis, and clean source.",
        inLanguage: "en-US",
        publisher: { "@id": `${SITE_URL}/#person` },
        potentialAction: {
          "@type": "SearchAction",
          target: {
            "@type": "EntryPoint",
            urlTemplate: `${SITE_URL}/problems?q={search_term_string}`,
          },
          "query-input": "required name=search_term_string",
        },
      },
      PERSON_LD,
    ],
  };
}

export function problemJsonLd(s: Solution) {
  const url = absoluteUrl(`/problems/${s.slug}`);
  const datePublished = s.firstCommittedAt;
  const dateModified = s.lastCommittedAt ?? s.firstCommittedAt;
  const body =
    s.approach.keyInsight ??
    s.approach.summary ??
    s.description ??
    s.approach.title;

  return {
    "@context": "https://schema.org",
    "@graph": [
      {
        "@type": "TechArticle",
        "@id": `${url}#article`,
        headline: `${s.number}. ${s.title} — LeetCode ${s.difficulty} C++ Solution`,
        name: s.title,
        description: truncateDescription(body),
        url,
        mainEntityOfPage: url,
        author: { "@id": `${SITE_URL}/#person` },
        creator: { "@id": `${SITE_URL}/#person` },
        publisher: { "@id": `${SITE_URL}/#person` },
        inLanguage: "en-US",
        articleSection: s.topicLabel,
        keywords: [
          "LeetCode",
          `LeetCode ${s.number}`,
          s.title,
          `${s.title} C++`,
          `${s.title} solution`,
          s.topicLabel,
          s.difficulty,
          "C++",
          "algorithms",
          "data structures",
        ].join(", "),
        about: { "@id": `${SITE_URL}/#website` },
        datePublished,
        dateModified,
        proficiencyLevel: s.difficulty,
      },
      {
        "@type": "SoftwareSourceCode",
        "@id": `${url}#code`,
        name: `${s.title} — C++`,
        codeRepository: OWNER.repo,
        programmingLanguage: "C++",
        runtimePlatform: "ISO C++17",
        targetProduct: { "@id": `${url}#article` },
        codeSampleType: "code snippet",
        text: s.code,
        url: s.githubUrl,
        author: { "@id": `${SITE_URL}/#person` },
      },
      {
        "@type": "BreadcrumbList",
        itemListElement: [
          {
            "@type": "ListItem",
            position: 1,
            name: "Home",
            item: SITE_URL,
          },
          {
            "@type": "ListItem",
            position: 2,
            name: "Problems",
            item: absoluteUrl("/problems"),
          },
          {
            "@type": "ListItem",
            position: 3,
            name: `${s.number}. ${s.title}`,
            item: url,
          },
        ],
      },
      PERSON_LD,
    ],
  };
}

export function problemMetadata(s: Solution): Metadata {
  const url = `/problems/${s.slug}`;
  const title = `${s.number}. ${s.title} — LeetCode ${s.difficulty} C++ Solution`;
  const body =
    s.approach.keyInsight ??
    s.approach.summary ??
    s.description ??
    `${s.title} solved in C++ with approach, complexity analysis, and source code.`;
  const description = truncateDescription(body);
  const keywords = [
    `LeetCode ${s.number}`,
    s.title,
    `${s.title} C++`,
    `${s.title} solution`,
    `LeetCode ${s.title}`,
    s.topicLabel,
    `${s.topicLabel} LeetCode`,
    `LeetCode ${s.difficulty}`,
    "C++ solution",
    "LeetCode C++",
    "algorithms",
    "data structures",
  ];

  return {
    title,
    description,
    keywords,
    authors: [{ name: OWNER.name, url: OWNER.portfolio }],
    alternates: { canonical: url },
    openGraph: {
      type: "article",
      url,
      title,
      description,
      siteName: `${OWNER.name} — LeetCode Solutions`,
      locale: "en_US",
      publishedTime: s.firstCommittedAt,
      modifiedTime: s.lastCommittedAt ?? s.firstCommittedAt,
      authors: [OWNER.portfolio],
      tags: [s.topicLabel, s.difficulty, "LeetCode", "C++"],
    },
    twitter: {
      card: "summary_large_image",
      title,
      description,
    },
  };
}
