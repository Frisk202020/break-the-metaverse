import { FileType } from "../parser";
import { dir_action, file_action, type SharedActionArgs } from "./action";
import { icon } from "./util";

interface Args {
    solution: string,
    shared_args: SharedActionArgs
} 

export default function Key(args: Args) {
    if (!args.shared_args.pending_file && !args.shared_args.pending_dir) {
        throw new Error("Nothing to unlock");
    }
    const isExe = args.shared_args.pending_file?.type === FileType.EXE;

    return <form style={{display: "flex", flexDirection: "column", alignItems: "center"}}>
        <label htmlFor="key">{isExe ? "Command line" : "File key"}</label>
        <div style={{display: "flex", alignItems: "center", justifyContent: "center"}}>
            {icon(isExe ? "code" : "key_vertical")}
            <input type="text" pattern="[A-Za-z0-9.\/ ]+" name="key" defaultValue={isExe ? `./${args.shared_args.pending_file!.name}.exe` : ""} required={true}></input>
        </div>
        <input type="submit" formAction={(x)=>form_action(x, args, isExe)} value="Unlock"></input>
    </form>
}

function form_action(x: FormData, args: Args, isExe: boolean) {
    args.shared_args.pending_file_setter(null);
    args.shared_args.pending_dir_setter(null);

    const key = x.get("key");
    if (!key || key.toString().toLowerCase() !== args.solution) { 
        if (!isExe) { args.shared_args.txt_setter({is_meta: false, content: ["Invalid key !"]}); } 
        return;
    }

    if (args.shared_args.pending_file) {
        args.shared_args.pending_file.unlocked = true;
        file_action(args.shared_args.pending_file!, args.shared_args);
    } else if (args.shared_args.pending_dir) {
        args.shared_args.pending_dir.dir.unlocked = true;
        dir_action(args.shared_args.pending_dir.dir, args.shared_args.pending_dir.params, args.shared_args.dir_setter, args.shared_args.pending_dir_setter)
    }
}