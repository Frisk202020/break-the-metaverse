#ifndef SERVER_H
#define SERVER_H

#include <stdbool.h>
#include <pthread.h>

const char* start_server(pthread_t* host);
bool send_message(char* message, int size);
void close_server();

#endif