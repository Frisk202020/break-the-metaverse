import { readFileSync } from "fs";
import parser from "../parser";
import Display from "./display";

export default function Computer(ip: string) {
    const data = parser(JSON.parse(readFileSync(`data/${ip}/data.json`, "utf-8")));
    
    return <Display data={data}></Display>
}