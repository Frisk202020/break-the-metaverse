"use client";

import { JSX, useEffect, useState } from "react"
import { type CpmFile, type Directory, FileType } from "../parser";

import "./style.css";
import {apply_default_theme, THEMES} from "./theme";

type Icon = "folder" | "text_snippet" | "settings" | "image" | "brush";
function icon(name: Icon) {
    return <span className="material-symbols-outlined">{name}</span>
}

export default function Display(args: {data: Directory}) {
    const [path, setPath] = useState(["0.0.0.0"]);
    const [current, setDir] = useState(args.data);
    const [themeEnabled, setThemeState] = useState(false);

    useEffect(()=>apply_default_theme(), []);

    return <div id="main">
        <div id="nav">
            <div id="nav-inner">{path.join("/")}</div>
        </div>
        <div id="files-container">
            {render_dir(current)}
        </div>
        <div id="theme">
            <div id="theme-selector" style={{opacity: themeEnabled ? 1 : 0}}>
                {THEMES}
            </div>
            <div id="theme-btn" onClick={()=>setThemeState(!themeEnabled)} className={themeEnabled ? "pressed" : ""}>
                <span>{icon("brush")}</span>
            </div>
        </div>
    </div>;   
}

function render_dir(x: Directory) {
    const dirs = x.directories.map(dir_elm);
    const files = x.files.map(file_elm);

    return <div id="files">
        {dirs}
        {files}
    </div>
}

function dir_elm(x: Directory, i: number) {
    return <div className="file" key={"d"+i}>
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