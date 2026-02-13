"use client";

import { JSX, useEffect, useState } from "react"
import { type CpmFile, type Directory, FileType } from "../parser";

import "./style.css";
import {apply_default_theme, THEMES} from "./theme";
import { DirectorySetter, Setter } from "./util";
import { dir_action, file_action, return_action } from "./action";

type Icon = "folder" | "text_snippet" | "settings" | "image" | "brush" | "undo" | "captive_portal" | "contract";
function icon(name: Icon) {
    return <span className="material-symbols-outlined">{name}</span>
}

export default function Display(args: {data: Directory, ip: string}) {
    const [path, path_setter] = useState([args.ip]);
    const [dir, dir_setter] = useState(args.data);
    const setter: DirectorySetter = { path, path_setter, dir, dir_setter };

    const [themeEnabled, setThemeState] = useState(false);
    const [loadedText, setText] = useState("");

    useEffect(()=>apply_default_theme(), []);

    return <div id="main">
        <div id="nav">
            <div id="nav-inner">{path.join("/")}</div>
        </div>
        <div id="main-container">
            {loadedText.length > 0 ? <p id="txt">{loadedText}</p> : render_dir(dir, setter, args.ip, setText)}
        </div>
        <div id="theme-selector" style={{opacity: themeEnabled ? 1 : 0}}>
            {THEMES}
        </div>
        <div id="buttons">
            <div id="theme-btn" onClick={()=>setThemeState(!themeEnabled)} className={themeEnabled ? "pressed" : ""}>
                {icon("brush")}
            </div>
            <div>
                {icon("captive_portal")}
            </div>
            <div id="return" onClick={()=>return_action(dir, setter, loadedText, setText)} style={{opacity: dir.parent ? 1 : 0}}>
                {icon("undo")}
            </div>
        </div>
    </div>;   
}

function render_dir(x: Directory, setter: DirectorySetter, ip: string, txt_setter: Setter<string>) {
    const dirs = x.directories.map((x,i)=>dir_elm(x,i,setter));
    const files = x.files.map((x,i)=>file_elm(x,i,ip,txt_setter));

    return <div id="files">
        {dirs}
        {files}
    </div>
}

function dir_elm(x: Directory, i: number, setter: DirectorySetter) {
    return <div className="file" key={"d"+i} onClick={()=>dir_action(x, setter)}>
        {icon("folder")}
        <p>{x.name}</p>
    </div>;
} function file_elm(x: CpmFile, i: number, ip:string, txt_setter: Setter<string>) {
    return <div className="file" key={"f"+i} onClick={()=>file_action(x, ip, txt_setter)}>
        {file_icon(x.type)}
        <p>{x.name}</p>
    </div>
} function file_icon(x: FileType): JSX.Element {
    switch(x) {
        case FileType.TXT: return icon("text_snippet");
        case FileType.IMG: return icon("image");
        case FileType.SYS: return icon("settings");
        case FileType.THM: return icon("brush");
        case FileType.PDF: return icon("contract");
    }
}