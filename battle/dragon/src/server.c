#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdatomic.h>

#include "util/include/print.h"
#include "util/include/str.h"

#define SIZE 1024

static int sock;
static atomic_bool alive = true;

static int client_fd;
static pthread_mutex_t client_lock;

void close_server() {
    println(LOG_INFO, "Shutting down");

    atomic_store(&alive, false);
    shutdown(sock, SHUT_RDWR);
    close(sock);    
}

void process_payload(Str* message_holder, char* buff, int size) {
    /**
     * const [s1, s2] = buff.split("\n");
     * if (s2 == NULL) {
     *   str_concat(*message_holder, s1, size);
     *   return;
     * }
     * 
     * str_concat(*message_holder, s1, s1.length);
     * process_message(*message_holder);
     * 
     * str_clean(*message_holder);
     * str_concat(*message_holder, s2, s2.length);
     */
}

void receiver(Str* payload_holder) {
    char buff[SIZE]; 
    
    while (atomic_load(&alive)) {
        int n = recv(client_fd, buff, SIZE, 0);

        switch (n) {
            case 0: return;
            case -1:
                println(LOG_WARN, "Unexpected error closed the socket");
                return;
            default:
                process_payload(payload_holder, buff, n);
        }
    }
}

bool send_message(char* message, int size) {
    pthread_mutex_lock(&client_lock);
    if (client_fd == -1) {
        pthread_mutex_unlock(&client_lock);
        println(LOG_WARN, "Can't send message : client disconnected");
        return false;
    }

    send(client_fd, message, size, 0);
    pthread_mutex_unlock(&client_lock);

    return true;
}

void* server_job(void* args) {
    struct sockaddr from;
    socklen_t sin_len;
    Str payload;

    while (atomic_load(&alive)) {
        sin_len = sizeof(from);

        pthread_mutex_lock(&client_lock);
        client_fd = accept(sock, &from, &sin_len);
        if (client_fd == -1) {
            pthread_mutex_unlock(&client_lock);
            if (alive) println(LOG_WARN, "Failed to accept a client");
            continue;
        }

        pthread_mutex_unlock(&client_lock);
        receiver(&payload);

        pthread_mutex_lock(&client_lock);
        if (client_fd >= 0) {
            close(client_fd);
            client_fd = -1;
        }
        pthread_mutex_unlock(&client_lock);
    }

    return NULL;
}

const char* start_server(pthread_t* host) {
    struct sockaddr_in svr_addr;
    int opt = 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return "Failed to initialize socket";

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(sock);
        return "Failed to set port as immediately reusable";
    }

    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    svr_addr.sin_port = htons(3001);

    if (bind(sock, (struct sockaddr*)&svr_addr, sizeof(svr_addr)) == -1) {
        close(sock);
        return "Failed to bind the socket";
    }

    listen(sock, 1);
    println(LOG_INFO, "Sever is listening on localhost:3001");

    pthread_mutex_init(&client_lock, NULL);
    pthread_create(host, NULL, server_job, NULL);

    return NULL;
}