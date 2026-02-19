import { type CpmFile, type Directory, FileType } from "../parser";
import { save_sequence } from "./server_actions";
import { apply_theme, type ThemeClass } from "./theme";
import { DirectoryParams, DisplayText, NavState, Sequence, Setter } from "./util";

const DELAY = 10;
let interrupt = false;
export function quit_metaverse() { interrupt = true; }

export function return_action(
    dir_params: DirectoryParams, dir_setter: Setter<DirectoryParams>, 
    txt: string[], txt_setter: Setter<DisplayText>, 
    pending_file: CpmFile|null, pending_file_setter: Setter<CpmFile|null>
) {
    if (txt.length > 0) {
        txt_setter({is_meta: false, content: []});
        return;
    } else if (pending_file) {
        return pending_file_setter(null);
    }

    if (!dir_params.dir.parent) { return; }

    dir_params.relative_path.pop();
    dir_setter({relative_path: dir_params.relative_path, dir: dir_params.dir.parent})
}

export function dir_action(x: Directory, dir_params: DirectoryParams, dir_setter: Setter<DirectoryParams>) {
    const new_path = dir_params.relative_path;
    new_path.push(x.name);

    dir_setter({relative_path: new_path, dir: x})
}

export interface SharedActionArgs {
    ip: string, 
    txt_setter: Setter<DisplayText>, 
    themes: Set<ThemeClass>, setThemes: Setter<Set<ThemeClass>>,
    pending_file: CpmFile | null, pending_file_setter: Setter<CpmFile | null>,
    set_sequence: Setter<Sequence>
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
                .then((x)=>args.txt_setter({is_meta: false, content: x.split("\n")}));
        case FileType.IMG:
        case FileType.PDF:
        case FileType.WEB:
            return window.open(path);
        case FileType.MT:
            return metaverse(x, args);
        case FileType.SYS:
        case FileType.EXE:
            if (x.attributes.text.length > 0) {
                args.txt_setter({is_meta: false, content: [x.attributes.text]});
            }
    }
}

async function metaverse(x:CpmFile, args: SharedActionArgs) {
    if (x.hack) {
        args.set_sequence(Sequence.Hack);
        save_sequence(Sequence.Hack)
    }

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
        args.txt_setter({is_meta: true, content: [txt]});
        await new Promise((r)=>setTimeout(r, DELAY));

        txt = txt + Math.round(Math.random()).toString();
    }
    args.txt_setter({is_meta: false, content:[]});
}

export function form_action(x: FormData, setIp: Setter<string>, txt_setter: Setter<DisplayText>, set_state: Setter<NavState>) {
    const ip = parse_ip(x);
    set_state(NavState.None);

    if (ip) {
        setIp(ip);
    } else {
        txt_setter({is_meta: false, content: ["Failed to connect: Invalid IP"]});
    }
} 

function parse_ip(x: FormData): string | null {
    const segments = [];
    for (const name of ["0", "1", "2", "3"]) {
        const value = x.get(name);
        if (!value) { return null; }
        segments.push(value);
    }

    return segments.join(".");
}