#ifndef SERVER_H
#define SERVER_H

#include <stdbool.h>

const char* start_server();
bool send_message(char* message, int size);

#endif