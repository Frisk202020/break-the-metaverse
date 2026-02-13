"use client"
import { useState } from "react";
import { Directory } from "../parser";
import Display from "./display";
import { HOME_IP } from "./util";

const DEV_DEFAULT = "0.0.0.1"
export default function Computer(args: {data: Map<string, Directory>}) {
    const [ip, setIp] = useState(DEV_DEFAULT);
    const data = args.data.get(ip);

    return <Display data={data === undefined ? args.data.get(HOME_IP)! : data} ip={data === undefined ? HOME_IP : ip} setIp={setIp}></Display>
}