"use client";

import { Dispatch, JSX, SetStateAction, useEffect, useState } from "react"
import { type CpmFile, type Directory, FileType } from "../parser";

import "./style.css";
import {apply_default_theme, THEMES} from "./theme";

type Icon = "folder" | "text_snippet" | "settings" | "image" | "brush" | "undo";
function icon(name: Icon) {
    return <span className="material-symbols-outlined">{name}</span>
}

type Setter<T> = Dispatch<SetStateAction<T>>;
interface DirectorySetter {
    path: string[],
    path_setter: Setter<string[]>,
    dir: Directory,
    dir_setter: Setter<Directory>
}

export default function Display(args: {data: Directory}) {
    const [path, path_setter] = useState(["0.0.0.0"]);
    const [dir, dir_setter] = useState(args.data);
    const setter: DirectorySetter = { path, path_setter, dir, dir_setter };
    const [themeEnabled, setThemeState] = useState(false);

    useEffect(()=>apply_default_theme(), []);

    return <div id="main">
        <div id="nav">
            <div id="nav-inner">{path.join("/")}</div>
        </div>
        <div id="files-container">
            {render_dir(dir, setter)}
        </div>
        <div id="theme">
            <div id="theme-selector" style={{opacity: themeEnabled ? 1 : 0}}>
                {THEMES}
            </div>
            <div id="theme-btn" onClick={()=>setThemeState(!themeEnabled)} className={themeEnabled ? "pressed" : ""}>
                {icon("brush")}
            </div>
        </div>
        <div id="return" onClick={()=>{
            if (!dir.parent) { return; }

            setter.dir_setter(dir.parent);
            setter.path.pop()
            setter.path_setter(setter.path);
        }} style={{opacity: dir.parent ? 1 : 0}}>
            {icon("undo")}
        </div>
    </div>;   
}

function render_dir(x: Directory, setter: DirectorySetter) {
    const dirs = x.directories.map((x,i)=>dir_elm(x,i,setter));
    const files = x.files.map(file_elm);

    return <div id="files">
        {dirs}
        {files}
    </div>
}

function dir_elm(x: Directory, i: number, setter: DirectorySetter) {
    return <div className="file" key={"d"+i} onClick={()=>{
        const new_path = setter.path;
        new_path.push(x.name);

        setter.path_setter(new_path);
        setter.dir_setter(x);
    }}>
        {icon("folder")}
        <p>{x.name}</p>
    </div>;
} function file_elm(x: CpmFile, i: number) {
    return <div className="file" key={"f"+i}>
        {file_icon(x.type)}
        <p>{x.name}</p>
    </div>
} function file_icon(x: FileType): JSX.Element {
    switch(x) {
        case FileType.TXT: return icon("text_snippet");
        case FileType.IMG: return icon("image");
        case FileType.SYS: return icon("settings");
    }
}