import { readFileSync } from "fs";

export enum FileType {
    TXT,
    IMG,
    SYS
} function parse_type(x: any): FileType {
    switch(x) {
        case "txt": return FileType.TXT;
        case "img": return FileType.IMG;
        case "sys": return FileType.SYS;
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
}

export default function parser(data: any): Directory {
    if (data.name === undefined) {
        throw new Error("Parsing failed: missing dir name");
    }
    if (!(data.files instanceof Array)) {
        throw new Error("Parsing failed : not a directory");
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

    return {
        name: data.name,
        files, directories
    };
}