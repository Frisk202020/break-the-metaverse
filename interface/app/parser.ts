export enum FileType {
    TXT,
    IMG,
    SYS,
    THM,
    PDF,
    MT
} function parse_type(x: any): FileType {
    switch(x) {
        case "txt": return FileType.TXT;
        case "img": return FileType.IMG;
        case "sys": return FileType.SYS;
        case "thm": return FileType.THM;
        case "pdf": return FileType.PDF;
        case "mt": return FileType.MT;
        default: throw new Error("Parsing failed: Invalid type");
    }
}

export interface CpmFile {
    name: string,
    type: FileType,
    path: string
} export interface Directory {
    name: string,
    files: CpmFile[],
    directories: Directory[],
    parent: Directory | null
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
                    path: x.attributes.path === undefined ? null : x.attributes.path
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