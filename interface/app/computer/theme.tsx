interface Property {
    name: string, value: string
} 

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

const THEME_MAP = new Map([
    ["light", new Theme("#faf4d4", "#2923d8", "#6964f8")],
    ["dark", new Theme("#1b1a1a", "#0c7f0c", "#355935")]
]);
const DEFAULT = THEME_MAP.get("light")!;

export const THEMES = Array.from(
    THEME_MAP.values().map((x, i)=>x.getElm(i))
);
export function apply_default_theme() {
    DEFAULT.apply();
}
export function apply_theme(name: string) {
    const t = THEME_MAP.get(name);
    if (t === undefined) { throw new Error("Invalid theme"); }

    t.apply();
}