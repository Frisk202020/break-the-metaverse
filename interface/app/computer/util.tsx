import { Dispatch, SetStateAction } from "react";
import type { Directory } from "../parser";

export const HOME_IP = "0.0.0.0";

export type Setter<T> = Dispatch<SetStateAction<T>>;
export interface DirectoryParams {
    dir: Directory,
    relative_path: string[]
} export interface DisplayText {
    is_meta: boolean,
    content: string[]
}

export type Icon = "folder" | "text_snippet" | "settings" | "image" | "brush" | "undo" | "captive_portal" | "contract" | "planet" | "key_vertical" | "code" | "globe";
export function icon(name: Icon) {
    return <span className="material-symbols-outlined">{name}</span>
}

export enum Sequence {
    Default,
    Hope,
    Hack
} export enum NavState {
    None, Thm, Form
}