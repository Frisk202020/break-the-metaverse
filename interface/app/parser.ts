export enum FileType {
    TXT,
    IMG,
    SYS,
    THM,
    PDF,
    MT,
    EXE
} function parse_type(x: any): FileType {
    switch(x) {
        case "txt": return FileType.TXT;
        case "img": return FileType.IMG;
        case "sys": return FileType.SYS;
        case "thm": return FileType.THM;
        case "pdf": return FileType.PDF;
        case "mt": return FileType.MT;
        case "exe": return FileType.EXE;
        default: throw new Error("Parsing failed: Invalid type");
    }
}

interface Attributes {
    path: string,
    key: string,
    text: string
} export interface CpmFile {
    name: string,
    type: FileType,
    unlocked: boolean,
    hack: boolean,
    attributes: Attributes
} export interface Directory {
    name: string,
    files: CpmFile[],
    directories: Directory[],
    parent: Directory | null
}

function unwrap_or_default(x?: string): string {
    return x === undefined ? "" : x;
}
export default function parser(data: any): Directory {
    if (data.name === undefined) {
        throw new Error("Parsing failed: missing dir name");
    }
    if (!(data.files instanceof Array)) {
        console.log(data);
        throw new Error("Parsing failed : not a directory - " + data.toString());
    }

    const files = Array<CpmFile>();
    const directories = Array<Directory>();
    for (const x of data.files) {
        if (x.attributes !== undefined) {
            if (x.name === undefined) { throw new Error("Parsing failed: missing file name"); }
            files.push(
                {
                    name: x.name, type: parse_type(x.attributes.type),
                    unlocked: x.attributes.key === undefined,
                    hack: x.attributes.hack !== undefined && x.attributes.hack,
                    attributes: {
                        path: unwrap_or_default(x.attributes.path),
                        key: unwrap_or_default(x.attributes.key),
                        text: unwrap_or_default(x.attributes.text) 
                    }
                }
            );
        } else {
            directories.push(parser(x));
        }
    }

    const self = {
        name: data.name,
        files, directories, parent: null
    };
    self.directories.forEach((x)=>x.parent = self);
    return self;
}

// parent to be assigned later
export function hacked_dir() {
    const dir: Directory = {
        name: "REDEMPTION",
        directories: [],
        files: [
            {name: "readme", type: FileType.TXT, unlocked: true, path: "README.txt", key: "", text: "" },
            {name: "pieces", type: FileType.EXE, unlocked: false, path: "", key: "./pieces.exe 19931 h0pe", text: "Decrypted 33 pieces"}
        ].map((x)=>{return {
            name: x.name, type: x.type, unlocked: x.unlocked, hack: false, attributes: {
                path: x.path, key: x.key, text: x.text
            }
        }}),
        parent: null
    }

    for (let i = 1; i < 19; i++) {
        dir.directories.push({name: i.toString(), files: [], directories: [], parent: dir});
    }
    dir.directories.push({
        name:"19", directories: [], parent: dir,
        files:[
            {"name":"readme", type: FileType.TXT, unlocked: true, hack: false, attributes: {
                path: "README.txt",
                key:"", text: ""
            }}
        ]
    });
    for (let i = 20; i < 100; i++) {
        dir.directories.push({name: i.toString(), files: [], directories: [], parent: dir});
    }

    return dir;
}