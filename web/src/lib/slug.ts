export function filenameToSlug(filename: string): string {
  const stem = filename.replace(/\.cpp$/, "");
  return stem.replace(/_/g, "-");
}

export function slugToPadded(slug: string): string {
  const match = slug.match(/^(\d{4})/);
  return match ? match[1] : slug.slice(0, 4);
}
