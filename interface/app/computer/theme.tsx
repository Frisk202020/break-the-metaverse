import { save_theme } from "./server_actions";
import { DEFAULT_SAVE, type Setter } from "./util";

interface Property {
    name: string, value: string
} 
export type ThemeClass = Theme;
class Theme {
    #bg: string;
    #bg_min: string;
    #border: string;
    #shadow: string;
    #properties: Property[];

    constructor(
        background: string, background_minor: string,
        icon: string, hover:string, shadow?: string
    ) {
        this.#bg = background; this.#bg_min = background_minor; 
        this.#border = icon;
        this.#shadow = shadow === undefined ? "none" : shadow;
        this.#properties = [
            {name: "--background", value: background},
            {name: "--background-minor", value: background_minor},
            {name: "--color", value: icon},
            {name: "--hover", value: hover},
            {name: "--shadow", value: this.#shadow}
        ];
    }
    getElm(id: number) {
        return <button 
            className="theme-icon" 
            onClick={()=>this.apply()}
            style={{backgroundImage: `linear-gradient(${this.#bg}, ${this.#bg_min} 90%)`, borderColor: this.#border, boxShadow: `.5vw .2vw .2vw ${this.#shadow}`}}
            key={"theme"+id}
        ></button>
    }

    apply() {
        this.#properties.forEach(
            (x)=>document.documentElement.style.setProperty(x.name, x.value)
        );
    }
}

const LIGHT = new Theme("#faf4d4", "#f7edb1", "#2923d8", "#6964f8"); 
const DARK = new Theme("#1b1a1a", "#0f0f0f", "#0c7f0c", "#355935");
const THEME_MAP = new Map([
    ["light", LIGHT],
    ["dark", DARK],
    ["void", new Theme("#000000", "#000000", "#ffffff", "#636363")],
    ["blood", new Theme("#bc1515", "#a91414", "#0e0664", "#d40202")],
    ["earth", new Theme("#6ac9f9", "#82d1f9", "#653e03", "#088b20")],
    ["gold", new Theme("#ffd700", "#f6dc48", "#b3b1b1", "#bf8970")],
    ["strawberry", new Theme("hsl(0 100% 85%)", "hsl(0, 93%, 67%)", "hsl(106 100% 29%)", "hsl(51 100% 50%)")],
    ["green", new Theme("#85e485", "#57dd57", "#036803", "#42a442")],
    ["dracula", new Theme("#4d0520", "#3b054d", "#a85016", "#360e5d", "#ffd700")],
    ["beach", new Theme("#fff67b", "#f7ec51", "#66ebef", "#fffbd5")],
    ["love", new Theme("#f565bd", "#db45a2", "#b216b5","#ef5990")],
    ["dusty", new Theme("#502e05", "#2e1a01", "#861010", "#8a670f")],
    ["shades", new Theme("#9f9f9f", "#797979", "#4b4a4a","#8f8f8f", "#2b2a2a")],
    ["white", new Theme("#ffffff", "#ffffff", "#ffffff","#ffffff")],
    ["neon", new Theme("#d011aac9", "#9a0fdfc9", "#1029cf", "#8316ae", "#eab429")],
    ["none", new Theme("transparent", "transparent", "transparent", "transparent")]
]);
const DEFAULT = THEME_MAP.get("light")!;
const DEFAULT_SAVED_THEMES = new Set(Array.from(DEFAULT_SAVE.themes).map((x)=>THEME_MAP.get(x)!));

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
        save_theme(name);
    }
    t.apply();
} export function load_themes(data: Set<string>) {
    const themes = [];
    for (const x of data) {
        const val = THEME_MAP.get(x);
        if (val === undefined) {
            console.log("Invalid themes file");
            return DEFAULT_SAVED_THEMES;
        }
        themes.push(val);
    }

    return new Set(themes);
}