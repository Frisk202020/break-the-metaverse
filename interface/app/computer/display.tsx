"use client";

import { JSX, useEffect, useState } from "react"
import { type CpmFile, type Directory, FileType } from "../parser";

import "./style.css";
import {apply_default_theme, THEMES} from "./theme";
import { DirectorySetter, Setter } from "./util";
import { dir_action, file_action, form_action, return_action, SharedActionArgs } from "./action";

type Icon = "folder" | "text_snippet" | "settings" | "image" | "brush" | "undo" | "captive_portal" | "contract" | "planet";
function icon(name: Icon) {
    return <span className="material-symbols-outlined">{name}</span>
}

export default function Display(args: {data: Directory, ip: string, setIp: Setter<string>}) {
    const [path, path_setter] = useState([args.ip]);
    const [dir, dir_setter] = useState(args.data);
    const setter: DirectorySetter = { path, path_setter, dir, dir_setter };

    const [themeEnabled, setThemeState] = useState(false); 
    const [themes, setThemes] = useState(THEMES)
    const themes_elm = Array.from(themes).map((x,i)=>x.getElm(i));

    const [formEnabled, setFormState] = useState(false);
    const [loadedText, setText] = useState<string[]>([]);

    useEffect(()=>apply_default_theme(), []);
    useEffect(()=>{
        dir_setter(args.data);
        setText([]);
        path_setter([args.ip]);
    }, [args.data]);

    return <div id="main">
        <div id="nav">
            <div id="nav-inner">{path.join("/")}</div>
        </div>
        <div id="main-container">
            {loadedText.length > 0 ? loadedText.map((x,i)=><p id="txt" key={"txt." + i}>{x}</p>) : render_dir(dir, setter, {
                ip: args.ip, txt_setter: setText, themes, setThemes
            })}
        </div>
        <div id="theme-selector" style={{opacity: themeEnabled ? 1 : 0, pointerEvents: themeEnabled ? "auto" : "none"}}>
            {themes_elm}
        </div>
        <div id="connect" style={{opacity: formEnabled ? 1 : 0, pointerEvents: formEnabled ? "auto" : "none"}}>
            <p>Connect to another computer</p>
            <form>
                <div>
                    {[0,1,2,3].map((x)=><input type="number" min="0" max="255" key={x} name={x.toString()} step={1} defaultValue="0" required={true}></input>)}  
                </div>
                <input type="submit" formAction={(x)=>form_action(x, args.setIp, setText, setFormState)} value="Ok"></input>
            </form>
        </div>
        <div id="buttons">
            <div id="theme-btn" onClick={()=>{setThemeState(!themeEnabled); setFormState(false);}} className={themeEnabled ? "pressed" : ""}>
                {icon("brush")}
            </div>
            <div className={formEnabled ? "pressed" : ""} onClick={()=>{setThemeState(false); setFormState(!formEnabled);}}>
                {icon("captive_portal")}
            </div>
            <div id="return" onClick={()=>return_action(dir, setter, loadedText, setText)} style={{opacity: dir.parent ? 1 : 0}}>
                {icon("undo")}
            </div>
        </div>
    </div>;   
}

function render_dir(x: Directory, setter: DirectorySetter, args: SharedActionArgs) {
    const dirs = x.directories.map((x,i)=>dir_elm(x,i,setter));
    const files = x.files.map((x,i)=>file_elm(x,i,args));

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
} function file_elm(x: CpmFile, i:number, args: SharedActionArgs) {
    return <div className="file" key={"f"+i} onClick={()=>file_action(x, args)}>
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
        case FileType.MT: return icon("planet");
    }
}