"use client"
import { useState } from "react";
import { Directory, hacked_dir, hope_dir } from "../parser";
import Display from "./display";
import { HOME_IP, Sequence } from "./util";

const HOPE = hope_dir();
const HACKED = hacked_dir();

export default function Computer(args: {data: Map<string, Directory>}) {
    const [ip, setIp] = useState(HOME_IP);
    const [sequence, set_sequence] = useState(Sequence.Default);

    let data = args.data.get(ip);
    if (data === undefined) { 
        console.log("IP not found"); 
        setIp("0.0.0.0");
    }

    switch(sequence) {
        case Sequence.Hope:
            try_append_directory(data!, HOPE, ip, 4);
            break;
        case Sequence.Hack:
            try_append_directory(data!, HACKED, ip, 5);
    }
    return <Display data={data!} ip={ip} setIp={setIp} set_sequence={set_sequence}></Display>
}

function try_append_directory(parent: Directory, child: Directory, ip: string, threshold: number) {
    if (ip === HOME_IP && parent.directories.length < threshold) {
        child.parent = parent;
        parent.directories.push(child);
    }
}