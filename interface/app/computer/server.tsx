import { readFileSync } from "fs";
import parser from "../parser";
import Computer from "./computer";

const IPS = [
    "0.0.0.0"
];

export default function Server() {
    const data = new Map(
        IPS.map((x)=>[
            x,
            parser(JSON.parse(readFileSync(`app/computer/data/${x}.json`, "utf-8")))
        ])
    )
    return <Computer data={data}></Computer>
}