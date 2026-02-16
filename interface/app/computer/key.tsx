import { file_action, type SharedActionArgs } from "./action";
import { icon } from "./util";

interface Args {
    solution: string,
    shared_args: SharedActionArgs
} export default function Key(args: Args) {
    return <form style={{display: "flex", flexDirection: "column", alignItems: "center"}}>
        <div style={{display: "flex", alignItems: "center", justifyContent: "center"}}>
            {icon("key_vertical")}
            <input type="text" pattern="[A-Za-z.]+" name="key"></input>
        </div>
        <input type="submit" formAction={(x)=>form_action(x, args)} value="Unlock"></input>
    </form>
}

function form_action(x: FormData, args: Args) {
    if (!args.shared_args.pending_file) {
        throw new Error("No file to unlock");
    }
    
    args.shared_args.pending_file_setter(null);
    const key = x.get("key");
    if (!key || key !== args.solution) { 
        args.shared_args.txt_setter(["Invalid key !"]); 
    }

    args.shared_args.pending_file.unlocked = true;
    file_action(args.shared_args.pending_file, args.shared_args);
}