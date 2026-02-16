import { type CpmFile, type Directory, FileType } from "../parser";
import { apply_theme, type ThemeClass } from "./theme";
import type { DirectorySetter, Setter } from "./util";

const DELAY = 10;
let interrupt = false;
export function quit_metaverse() { interrupt = true; }

export function return_action(dir: Directory, setter: DirectorySetter, txt: string[], txt_setter: Setter<string[]>) {
    if (txt.length > 0) {
        txt_setter([]);
        return;
    }

    if (!dir.parent) { return; }

    setter.dir_setter(dir.parent);
    setter.path.pop()
    setter.path_setter(setter.path);
}

export function dir_action(x: Directory, setter: DirectorySetter) {
    const new_path = setter.path;
    new_path.push(x.name);

    setter.path_setter(new_path);
    setter.dir_setter(x);
}

export interface SharedActionArgs {
    ip: string, 
    txt_setter: Setter<string[]>, 
    themes: Set<ThemeClass>, setThemes: Setter<Set<ThemeClass>>,
    meta_setter: Setter<string>,
    pending_file: CpmFile | null, pending_file_setter: Setter<CpmFile | null>
}
export function file_action(x: CpmFile, args: SharedActionArgs) {
    if (!x.unlocked && x.attributes.key !== undefined) {
        return args.pending_file_setter(x);
    }

    const path = `/${args.ip}/${x.attributes.path}`;
    switch(x.type) {
        case FileType.THM: return apply_theme(x.name, args.themes, args.setThemes);
        case FileType.TXT: 
            return fetch(path)
                .then((res)=>{
                    if (!res.ok) {
                        throw new Error("Fetch error:"+res.status);
                    }
                    return res.text();
                })
                .then((x)=>args.txt_setter(x.split("\n")));
        case FileType.IMG:
        case FileType.PDF:
            return window.open(path);
        case FileType.MT:
            return (async ()=>{
                if (x.attributes.path.length > 0) {
                    window.open(`/${args.ip}/${x.attributes.path}`);
                }
                interrupt = false;

                const elm = document.getElementById("meta-screen")!;
                let txt = "0";
                while(!interrupt) {
                    if (elm.scrollHeight > elm.clientHeight) {
                        txt = "0";
                    }
                    args.meta_setter(txt);
                    await new Promise((r)=>setTimeout(r, DELAY));

                    txt = txt + Math.round(Math.random()).toString();
                }
                args.meta_setter("");
            })();
        case FileType.SYS:
            if (x.attributes.text.length > 0) {
                args.txt_setter([x.attributes.text]);
            }
    }
}

export function form_action(x: FormData, setIp: Setter<string>, txt_setter: Setter<string[]>, enabler: Setter<boolean>) {
    const ip = parse_ip(x);
    enabler(false);

    if (ip) {
        setIp(ip);
    } else {
        txt_setter(["Failed to connect: Invalid IP"]);
    }
} function parse_ip(x: FormData): string | null {
    const segments = [];
    for (const name of ["0", "1", "2", "3"]) {
        const value = x.get(name);
        if (!value) { return null; }
        segments.push(value);
    }

    return segments.join(".");
}