import { HOME_IP, Setter } from "./util";

export default function Fallback(args: {src: string | null, setIp: Setter<string>}) {
    return <div>
        <p>Connection failed...</p>
        <button onClick={()=>args.setIp(args.src ? args.src : HOME_IP)}>Go back to home</button>
    </div>;
}