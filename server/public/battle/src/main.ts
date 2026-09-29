import { GameManager } from "./class/GameManager.js";

declare var battle: string;

function main(): void {
    const gm = new GameManager(battle);
    if (!gm.isValid()) {
        console.log(`Invalid battle : ${battle}`);
        return;
    }
}

main();