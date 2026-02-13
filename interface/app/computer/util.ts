import { Dispatch, SetStateAction } from "react";
import { Directory } from "../parser";

export const HOME_IP = "0.0.0.0";

export type Setter<T> = Dispatch<SetStateAction<T>>;
export interface DirectorySetter {
    path: string[],
    path_setter: Setter<string[]>,
    dir: Directory,
    dir_setter: Setter<Directory>
}