import type { Metadata } from "next";

export const metadata: Metadata = {
  title: "Break the Metaverse",
  description: "Flavie's interface",
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en">
      <body>
        {children}
      </body>
    </html>
  );
}
