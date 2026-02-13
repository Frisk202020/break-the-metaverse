"use client"
import { useState } from "react";
import { Directory } from "../parser";
import Display from "./display";
import Fallback from "./fallback";
import { HOME_IP } from "./util";

export default function Computer(args: {data: Map<string, Directory>}) {
    const [src, setSrc] = useState<string | null>(null)
    const [ip, setIp] = useState(HOME_IP);
    const data = args.data.get(ip);
    if (data === undefined) {
        return <Fallback src={src} setIp={setIp}></Fallback>
    }

    return <Display data={data} ip={ip}></Display>
}