import { readFile, writeFile } from "fs/promises";
import { NextResponse } from "next/server";

const path = "app/scan/data.txt";
const isIP = /\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b/;

export const POST = async () => {
    await writeFile(path, "false", { flag: "w" });
    let res: string | null | false = false;

    while (res === false) {
        const x = (await readFile(path)).toString();
        switch(x) {
            case "null": res = null; break;
            case "false": break;
            default: 
                if (isIP.test(x)) res = x;
                else res = null;

                await writeFile(path, "false", { flag: "w" });
        }
    }

    return NextResponse.json({ content: res ?? "" });
}

export const PUT = async (request: Request) => {
    const body = await request.json();
    if (!body || !body.content || (!isIP.test(body.content) && body.content !== "null")) 
        return NextResponse.json({}, { status: 400 });

    await writeFile(path, body.content, { flag: "w" });
    return NextResponse.json({});
}