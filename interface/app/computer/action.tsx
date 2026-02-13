import { CpmFile, Directory, FileType } from "../parser";
import { apply_theme } from "./theme";
import { DirectorySetter, Setter } from "./util";

export function return_action(dir: Directory, setter: DirectorySetter, txt: string, txt_setter: Setter<string>) {
    if (txt.length > 0) {
        txt_setter("");
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

export function file_action(x: CpmFile, ip: string, txt_setter: Setter<string>) {
    const path = `/${ip}/${x.path}`;
    switch(x.type) {
        case FileType.THM: return apply_theme(x.name);
        case FileType.TXT: 
            return fetch(path)
                .then((res)=>{
                    if (!res.ok) {
                        throw new Error("Fetch error:"+res.status);
                    }
                    return res.text();
                })
                .then((x)=>txt_setter(x));
        case FileType.IMG:
        case FileType.PDF:
            window.open(path);
    }
}

export function form_action(x: FormData, setIp: Setter<string>, txt_setter: Setter<string>, enabler: Setter<boolean>) {
    const ip = parse_ip(x);
    enabler(false);

    if (ip) {
        setIp(ip);
    } else {
        txt_setter("Failed to connect: Invalid IP");
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