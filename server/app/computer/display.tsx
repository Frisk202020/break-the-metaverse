"use client";

import { CSSProperties, JSX, useEffect, useState } from "react"
import { type CpmFile, type Directory, FileType } from "../parser";

import "./style.css";
import {apply_default_theme, load_themes} from "./theme";
import { type DirectoryParams, type DisplayText, type Icon, icon, NavState, SaveData, Sequence, type Setter } from "./util";
import { dir_action, file_action, form_action, quit_metaverse, return_action, type SharedActionArgs } from "./action";
import Key from "./key";
import { clear_save, save_ip, save_sequence } from "./server_actions";

function hidden_box_style(state: NavState, expected_state: NavState): CSSProperties {
    return state === expected_state ? {
        opacity: 1, pointerEvents: "auto"
    } : {
        opacity: 0, pointerEvents: "none"
    }
} 

interface BtnParams {
    onclick: ()=>void,
    classname: string
} function btn_elm(state: NavState, expected_state: NavState, set_state: Setter<NavState>, icon_name: Icon, id?: string) {
    const params: BtnParams = state === expected_state
        ? {onclick: ()=>set_state(NavState.None), classname: "pressed"}
        : {onclick: ()=>set_state(expected_state), classname: ""};

    return <div id={id === undefined ? "" : id} onClick={params.onclick} className={params.classname}>
        {icon(icon_name)}
    </div>
}

enum Arrows {
    Up ="ArrowUp",
    Down = "ArrowDown",
    Left = "ArrowLeft",
    Right = "ArrowRight"
} 
const spell = [Arrows.Up, Arrows.Left, Arrows.Up, Arrows.Right, Arrows.Down, Arrows.Right];
const event = (event: KeyboardEvent)=>{
    if (event.key === spell[spell_index]) {
        spell_index++;
        if (spell_index === spell.length) {
            clear_save();
            spell_index = 0;
        }
    } else {
        spell_index = 0;
    }
}
let spell_index = 0;

function connect_handler(ip: string, set_ip: Setter<string>, set_state: Setter<NavState>) {
    set_state(NavState.None);
    set_ip(ip);
}

function visited_ip_btn(x: string, i: number, set_ip: Setter<string>, set_nav: Setter<NavState>) {
    return <button
        onClick={()=>connect_handler(x, set_ip, set_nav)}
        key={"visited_ip"+i}
    >{x}</button>
}

export default function Display(args: {data: Directory, save_data: SaveData, ip: string, setIp: Setter<string>, set_sequence: Setter<Sequence>}) {
    const [dir_params, dir_setter] = useState<DirectoryParams>({relative_path: [args.ip], dir: args.data});
    const [nav_state, set_nav_state] = useState(NavState.None);

    const [themes, setThemes] = useState(load_themes(args.save_data.themes))
    const themes_elm = Array.from(themes).map((x,i)=>x.getElm(i));

    const [txt, set_txt] = useState<DisplayText>({is_meta: false, content: []})
    const metaScreenStyle = txt.is_meta ? 100 : 0;

    const [pending_file, pending_file_setter] = useState<CpmFile | null>(null);
    const visited_ips_elm = Array.from(args.save_data.ips).map((x,i)=>visited_ip_btn(x,i,args.setIp,set_nav_state));

    useEffect(()=>{
        apply_default_theme();
        document.addEventListener("keydown", event);
    }, []);
    useEffect(()=>{
        dir_setter({dir: args.data, relative_path: [args.ip]});
        set_txt({is_meta: false, content: []});
        if (args.data.name === "hope") {
            args.set_sequence(Sequence.Hope);
            save_sequence(Sequence.Hope);
        }

        if (!args.save_data.ips.has(args.ip)) {
            args.save_data.ips.add(args.ip);
            visited_ips_elm.push(visited_ip_btn(args.ip,visited_ips_elm.length,args.setIp,set_nav_state));
            save_ip(args.ip);
        }
    }, [args.data]);

    return <div id="main">
        <div id="nav">
            <div id="nav-inner">{dir_params.relative_path.join("/")}</div>
        </div>
        <div id="main-container">
            {render_main(dir_params, dir_setter, txt.content, pending_file, {
                ip: args.ip, txt_setter: set_txt, themes, setThemes, pending_file, pending_file_setter, set_sequence: args.set_sequence
            })}
        </div>
        <div id="theme-selector" style={hidden_box_style(nav_state, NavState.Thm)}>
            {themes_elm}
        </div>
        <div id="connect" style={hidden_box_style(nav_state, NavState.Form)}>
            <p>Connect to another computer</p>
            <div>
                <div>
                    <p>Query a new computer</p>
                    <form>
                        <div>
                            {[0,1,2,3].map((x)=><input type="number" min="0" max="999" key={x} name={x.toString()} step={1} defaultValue="0" required={true}></input>)}  
                        </div>
                        <input type="submit" formAction={(x)=>form_action(x, args.setIp, set_txt, set_nav_state)} value="Ok"></input>
                    </form>
                </div>
                <div>
                    <p>Visit a known address</p>
                    <div id="visited">
                        {visited_ips_elm}
                    </div>
                </div>
            </div>
        </div>
        <div id="buttons">
            {btn_elm(nav_state, NavState.Thm, set_nav_state, "brush", "theme-btn")}
            {btn_elm(nav_state, NavState.Form, set_nav_state, "captive_portal")}
            <div id="return" onClick={()=>return_action(dir_params, dir_setter, txt.content, set_txt, pending_file, pending_file_setter)} style={{opacity: dir_params.dir.parent ? 1 : 0}}>
                {icon("undo")}
            </div>
        </div>
        <div id="meta-screen" style={{width: `${metaScreenStyle}vw`, height: `${metaScreenStyle}vh`, opacity: txt.is_meta ? 1 : 0}}>
            <p>{txt.content[0]}</p>
            <div onClick={()=>quit_metaverse()}>{icon("undo")}</div>
        </div>
    </div>;   
}

function render_main(
    dir_params: DirectoryParams, dir_setter: Setter<DirectoryParams>, 
    loadedText: string[], 
    pending_file: CpmFile | null, args: SharedActionArgs
) {
    if (loadedText.length > 0) {
        return loadedText.map((x,i)=><p id="txt" key={"txt." + i}>{x}</p>);
    } else if (pending_file) {
        return <Key solution={pending_file.attributes.key} shared_args={args}></Key>
    } else {
        return render_dir(dir_params, dir_setter, args);
    }
}

function render_dir(dir_params: DirectoryParams, dir_setter: Setter<DirectoryParams>, args: SharedActionArgs) {
    const dirs = dir_params.dir.directories.map((x,i)=>dir_elm(x,i,dir_params, dir_setter));
    const files = dir_params.dir.files.map((x,i)=>file_elm(x,i,args));

    return <div id="files">
        {dirs}
        {files}
    </div>
}

function dir_elm(x: Directory, i: number, dir_params: DirectoryParams, dir_setter: Setter<DirectoryParams>) {
    return <div className="file" key={"d"+i} onClick={()=>dir_action(x, dir_params, dir_setter)}>
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
        case FileType.EXE: return icon("code");
        case FileType.WEB: return icon("globe");
    }
}