"use client"
import { useState } from "react";
import { Directory } from "../parser";
import Display from "./display";
import { HOME_IP } from "./util";

export default function Computer(args: {data: Map<string, Directory>}) {
    const [ip, setIp] = useState(HOME_IP);
    const data = args.data.get(ip);

    return <Display data={data === undefined ? args.data.get(HOME_IP)! : data} ip={data === undefined ? HOME_IP : ip} setIp={setIp}></Display>
}