"use client"

import { useState } from "react";

export default function Page() {
    const [txt, setTxt] = useState("");

    const buttons = [
        ["Intro room", "0.0.0.1"],
        ["Clover room", "341.721.107.2"],
        ["Hitchmann", "178.170.160.780"],
        ["Poor", "254.651.235.272"],
        ["RickRoll", "961.342.001.062"],
        ["Feignard", "138.433.302.268"]
    ].map(([name, ip], i) => <button 
        key={`btn.${i}`}
        style={{margin: "1vh"}}
        onClick={() => {
            fetch("scan", { body: JSON.stringify({ content: ip }), method: "PUT" }).then((res) => {
                setTxt(res.ok ? `Sent ${ip}` : "Failed to send a scan result, check console logs");
                new Promise((r) => setTimeout(r, 3000)).then(() => setTxt(""));
            });
        }}
    >{name} ({ip})</button>);

    return <div style={{
        display: "flex",
        flexDirection: "column",
        alignItems: "center",
    }}>
        <p style={{opacity: txt === "" ? 0 : 1}}>Output: {txt}</p>
        {buttons}
    </div>
}