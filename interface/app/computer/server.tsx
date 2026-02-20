import { readdirSync, readFileSync } from "fs";
import parser from "../parser";
import Computer from "./computer";
import { load } from "./server_actions";

const ROOT = "app/computer/data/computers";
const IPS = readdirSync(ROOT)
    .map((x)=>x.split(".json")[0]);

export default async function Server() {
    const save_data = await load(); 
    const data = new Map(
        IPS.map((x)=>[
            x,
            parser(JSON.parse(readFileSync(`${ROOT}/${x}.json`, "utf-8")))
        ])
    );
    return <Computer data={data} save_data={save_data}></Computer>
}