"use server";

import { appendFile, readFile, writeFile } from "fs/promises";
import { DEFAULT_SAVE, SaveData, Sequence } from "./util";

const ROOT = "app/computer/data/save/";
function format(file: string) {
    return `${ROOT}save_${file}.txt`;
}

const path = (name: string, backup: boolean) => format(name + (backup ? "_backup" : ""));

const IPS_PATH = (backup = false) => path("ips", backup); 
const THEMES_PATH = (backup = false) => path("themes", backup);
const SEQ_PATH = (backup = false) => path("sequence", backup);

const DEFAULT_SAVE_STRING = {
    themes: Array.from(DEFAULT_SAVE.themes).join(","),
    ips: Array.from(DEFAULT_SAVE.ips).join(",")
}

async function parse(path: string) {
    return (await readFile(path)).toString().split(",");
} async function parse_sequence() {
    switch ((await readFile(SEQ_PATH())).toString()) {
        case "0": return Sequence.Default;
        case "1": return Sequence.Hope;
        case "2": return Sequence.Map;
        case "3": return Sequence.Hack;
        default: console.log("Unrecognized sequence"); return Sequence.Default;
    }
} 

export async function load(): Promise<SaveData> {
    const resolve = await Promise.all([
        parse(THEMES_PATH()), parse(IPS_PATH()), parse_sequence()
    ]);
    
    return {
        themes: new Set(resolve[0]),
        ips: new Set(resolve[1]),
        sequence: resolve[2]
    };
}

function save(path: string, data: string) {
    appendFile(path, ","+data);
} export async function save_theme(theme: string) {
    save(THEMES_PATH(), theme);
} export async function save_ip(ip: string) {
    save(IPS_PATH(), ip);
} export async function save_sequence(seq: Sequence) {
    writeFile(SEQ_PATH(), seq.toString(), {flag: "w"});
}

export async function clear_save() {
    const promises = [THEMES_PATH(true), IPS_PATH(true), SEQ_PATH(true)].map((x) => readFile(x));
    const [themes, ips, sequence] = (await Promise.all(promises)).map((x) => x.toString());

    writeFile(THEMES_PATH(true), themes, { flag: "w" });
    writeFile(IPS_PATH(true), ips, { flag: "w" });
    writeFile(SEQ_PATH(true), `${sequence}`, { flag: "w" });

    writeFile(THEMES_PATH(), DEFAULT_SAVE_STRING.themes, { flag: "w" }); 
    writeFile(IPS_PATH(), DEFAULT_SAVE_STRING.ips, { flag: "w" }); 
    writeFile(SEQ_PATH(), "0", {flag: "w"});
}