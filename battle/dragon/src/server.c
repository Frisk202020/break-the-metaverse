#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#include "str.h"

#define SIZE 1024

int sock;

int client_fd;
pthread_mutex_t lock;

void process_message(Str s) {

}

void receiver() {
    Str message = str_new();

    while (true) {
        char buff[SIZE];
        int n = recv(client_fd, buff, SIZE, 0);  

        switch (n) {
            case -1:
                printf("Failed to receive a buffer : closing connection");
                pthread_mutex_lock(&lock);
                close(client_fd);
                client_fd = -1;
                pthread_mutex_unlock(&lock);
                return;

            default:
                str_concat(&message, buff, n);
            case 0:
                process_message(message);
                str_clean(&message);
                break;

            case SIZE:
                str_concat(&message, buff, SIZE);
                break;
        }
    }
}

bool send_message(char* message, int size) {
    pthread_mutex_lock(&lock);
    if (client_fd == -1) {
        pthread_mutex_unlock(&lock);
        printf("Can't send message : client disconnected");
        return false;
    }

    send(client_fd, message, size, 0);
    pthread_mutex_unlock(&lock);
}

void server_job(void* args) {
    struct sockaddr_in from;
    int sin_len;

    while (true) {
        pthread_mutex_lock(&lock);
        client_fd = accept(sock, &from, &sin_len);
        if (client_fd == -1) {
            pthread_mutex_unlock(&lock);
            printf("Failed to accept a client");
            continue;
        }

        pthread_mutex_unlock(&lock);
        receiver();
    }
}

const char* start_server() {
    pthread_t thread;
    struct sockaddr_in svr_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return "Failed to intialize socket";

    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = INADDR_LOOPBACK;
    svr_addr.sin_port = htons(3001);

    if (bind(sock, &svr_addr, sizeof(svr_addr)) == -1) {
        close(sock);
        return "Failed to bind the socket";
    }

    listen(sock, 1);
    pthread_mutex_init(&lock, NULL);
    pthread_create(&thread, NULL, server_job, NULL);
}