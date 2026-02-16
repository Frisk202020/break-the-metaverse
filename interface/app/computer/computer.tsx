"use client"
import { useState } from "react";
import { Directory, hacked_dir } from "../parser";
import Display from "./display";
import { HOME_IP } from "./util";

const DEV_DEFAULT = "0.0.0.0";
const HACKED = hacked_dir();

export default function Computer(args: {data: Map<string, Directory>}) {
    const [ip, setIp] = useState(DEV_DEFAULT);
    const [hacked, hack] = useState(false);

    const data = args.data.get(ip);
    if (ip === HOME_IP && hacked) {
        if (data === undefined) { throw new Error("Home file not found"); }
        if (data.directories.length < 4) {
            HACKED.parent = data;
            data.directories.push(HACKED);
        }
        return <Display data={data} ip={ip} setIp={setIp} hack={hack}></Display>
    } else {
        if (data === undefined) { console.log("file not found"); }
        return <Display data={data === undefined ? args.data.get(HOME_IP)! : data} ip={data === undefined ? HOME_IP : ip} setIp={setIp} hack={hack}></Display>
    }
}