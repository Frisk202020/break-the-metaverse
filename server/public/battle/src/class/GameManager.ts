import { Entity } from "./Entity.js";
import { Socket } from "./Socket.js";


export class GameManager {
    #entities: Entity[];
    #socket: Socket;
    #isValid: boolean;
    
    constructor(battle: string) {
        switch(battle) {
            case "dragon": this.#entities = GameManager.#startDragon(); break;
            case "sensei": this.#entities = GameManager.#startSensei(); break;
            case "spirit": this.#entities = GameManager.#startSpirit(); break;
            case "final": this.#entities = GameManager.#startFinal(); break;
            default: this.#entities = []; this.#isValid = false; this.#socket = new Socket(false); return;
        }

        this.#isValid = true;
        this.#socket = new Socket(true);
    }

    isValid(): boolean {
        return this.#isValid;
    }

    static #startDragon(): Entity[] {
        return [
            new Entity("Derek", 80),
            new Entity("Flavie", 80),
            new Entity("Haloise", 80),
            new Entity("Clover", 80),
            new Entity("Xhara", 80),
            new Entity("Dragon", 1000)
        ]
    }

    static #startSensei(): Entity[] {
        return ["Derek", "Flavie", "Haloise", "Clover", "Xhara"]
            .map((x) => new Entity(x, 10))
            .concat([new Entity("Sensei", 20)])
    }

    static #startSpirit(): Entity[] {
        return ["Derek", "Flavie", "Haloise", "Clover", "Xhara"]
            .map((x) => new Entity(x, 100))
            .concat([new Entity("Spirit", 1)])
    }

    static #startFinal(): Entity[] {
        return [
            new Entity("Derek", 80),
            new Entity("Flavie", 80),
            new Entity("Haloise", 80),
            new Entity("Clover", 80),
            new Entity("Xhara", 80),
            new Entity("Virus", 1500),
            new Entity("H0PE", 500)
        ]
    }
}