#ifndef FIREWALL
#define FIREWALL

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    bool checked;
    int position;
    char value;
}state;

void print_matrix(char** arr, int size);

void free_matrix(char** arr, int s);

/**
* @brief checks if the firewall is entirely deciphered
*/
bool done(state* s, int lines);

/**
* @brief checks if a prompt (between prompt[e] and prompt[d]) corresponds to a pre-set string
*/
bool equal(char* s, char* prompt, int d, int e);

/**
* @brief reveals the firewall
*/
void analyze(char** wall, int lines, char* sol, int* left, state* s);

/**
* @brief tool from string.h to check the equality of two strings
*/
int strcmp(const char* s1, const char* s2);

/**
* @brief simulates a Hacknet firewall with its solution "sol"
*/
void firewall(int lines, char* sol, float cooldown, int timer);

#endif