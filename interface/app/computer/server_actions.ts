"use server";

import { appendFile, readFile, writeFile } from "fs/promises";
import { DEFAULT_SAVE, SaveData, Sequence } from "./util";

const ROOT = "app/computer/data/save/";
function format(file: string) {
    return `${ROOT}save_${file}.txt`;
}
const IPS_PATH = format("ips"); const THEMES_PATH = format("themes");
const SEQ_PATH = format("sequence");

const DEFAULT_SAVE_STRING = {
    themes: Array.from(DEFAULT_SAVE.themes).join(","),
    ips: Array.from(DEFAULT_SAVE.ips).join(",")
}

async function parse(path: string) {
    return (await readFile(path)).toString().split(",");
} async function parse_sequence() {
    switch ((await readFile(SEQ_PATH)).toString()) {
        case "0": return Sequence.Default;
        case "1": return Sequence.Hope;
        case "2": return Sequence.Hack;
        default: console.log("Unrecognized sequence"); return Sequence.Default;
    }
} 

export async function load(): Promise<SaveData> {
    const resolve = await Promise.all([
        parse(THEMES_PATH), parse(IPS_PATH), parse_sequence()
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
    save(THEMES_PATH, theme);
} export async function save_ip(ip: string) {
    save(IPS_PATH, ip);
} export async function save_sequence(seq: Sequence) {
    writeFile(SEQ_PATH, seq.toString(), {flag: "w"});
}


export async function clear_save() {
    writeFile(THEMES_PATH, DEFAULT_SAVE_STRING.themes, {
        flag: "w"
    }); writeFile(IPS_PATH, DEFAULT_SAVE_STRING.ips, {
        flag: "w"
    }); writeFile(SEQ_PATH, "0", {flag: "w"});
}