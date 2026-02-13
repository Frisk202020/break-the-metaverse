import { Setter } from "./util";

interface Property {
    name: string, value: string
} 
export type ThemeClass = Theme;
class Theme {
    #color: string;
    #properties: Property[];

    constructor(
        background: string, icon: string, hover:string
    ) {
        this.#color = background;
        this.#properties = [
            {name: "--background", value: background},
            {name: "--color", value: icon},
            {name: "--hover", value: hover}
        ];
    }
    getElm(id: number) {
        return <button 
            className="theme-icon" 
            onClick={()=>this.apply()}
            style={{backgroundColor: this.#color}}
            key={"theme"+id}
        ></button>
    }

    apply() {
        this.#properties.forEach(
            (x)=>document.documentElement.style.setProperty(x.name, x.value)
        );
    }
}

const LIGHT = new Theme("#faf4d4", "#2923d8", "#6964f8"); 
const DARK = new Theme("#1b1a1a", "#0c7f0c", "#355935");
const THEME_MAP = new Map([
    ["light", LIGHT],
    ["dark", DARK],
    ["void", new Theme("#000000", "#ffffff", "#636363")]
]);
const DEFAULT = THEME_MAP.get("light")!;

export const THEMES = new Set([LIGHT, DARK]);
export function apply_default_theme() {
    DEFAULT.apply();
}
export function apply_theme(name: string, themes: Set<Theme>, themes_setter: Setter<Set<Theme>>) {
    const t = THEME_MAP.get(name);
    if (t === undefined) { throw new Error("Invalid theme"); }

    if (!themes.has(t)) {
        const new_set = new Set(themes);
        new_set.add(t);
        themes_setter(new_set);
    }
    t.apply();
}