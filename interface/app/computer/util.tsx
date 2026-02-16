import { Dispatch, SetStateAction } from "react";
import type { Directory } from "../parser";

export const HOME_IP = "0.0.0.0";

export type Setter<T> = Dispatch<SetStateAction<T>>;
export interface DirectorySetter {
    path: string[],
    path_setter: Setter<string[]>,
    dir: Directory,
    dir_setter: Setter<Directory>
}

type Icon = "folder" | "text_snippet" | "settings" | "image" | "brush" | "undo" | "captive_portal" | "contract" | "planet" | "key_vertical" | "code";
export function icon(name: Icon) {
    return <span className="material-symbols-outlined">{name}</span>
}