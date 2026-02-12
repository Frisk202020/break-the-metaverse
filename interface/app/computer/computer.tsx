import { readFileSync } from "fs";
import parser from "../parser";
import Display from "./display";

export default function Computer(ip: string) {
    const data = parser(JSON.parse(readFileSync(`app/computer/${ip}/data.json`, "utf-8")));
    
    return <Display data={data}></Display>
}