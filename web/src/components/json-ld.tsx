interface Props {
  data: object;
  id?: string;
}

export function JsonLd({ data, id }: Props) {
  return (
    <script
      type="application/ld+json"
      id={id}
      // Intentional: schema.org payloads are inert JSON-LD with no script execution.
      dangerouslySetInnerHTML={{
        __html: JSON.stringify(data).replace(/</g, "\\u003c"),
      }}
    />
  );
}
