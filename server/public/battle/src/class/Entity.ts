export class Entity {
    #name: string;
    #maxHP: number;
    #hp: number;
    #actions: string[];

    constructor(name: string, hp: number) {
        this.#name = name;
        this.#maxHP = hp;
        this.#hp = hp;
        this.#actions = [];
    }
}