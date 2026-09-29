export class Socket {
    #socket?: WebSocket;
    #queue: string[];
    static finished = false;

    constructor(connect: boolean) {
        this.#queue = [];
        if (connect) this.connect();
    }

    #handleFailure(reason: string) {
        this.#socket = undefined;
        if (Socket.finished) return;

        console.log(`${reason}, retrying...`);
        this.connect();
    }

    connect() {
        this.#socket = new WebSocket("ws://localhost:3001");

        this.#socket.onerror = () => this.#handleFailure("An error closed the socket");
        this.#socket.onclose = () => this.#handleFailure("Socket closed");
        this.#socket.onmessage = (ev) => {

        }

        let msg = this.#queue.shift();
        while (this.#socket && msg) {
            this.#socket.send(msg);
            msg = this.#queue.shift();
        }
    }

    send(msg: string) {
        if (!this.#socket) {
            this.#queue.push(msg);
            return;
        }

        this.#socket.send(msg);
    }
}