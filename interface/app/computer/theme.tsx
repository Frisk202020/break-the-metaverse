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

const THEMES_OBJECTS = [
    new Theme("#faf4d4", "#2923d8", "#6964f8"),
    new Theme("#1b1a1a", "#0c7f0c", "#355935"), 
];
const DEFAULT = THEMES_OBJECTS[1];

export const THEMES = THEMES_OBJECTS.map((x, i)=>x.getElm(i));
export function apply_default_theme() {
    DEFAULT.apply();
}