#include "util/include/print.h"

static LogLevel Level = LOG_INFO;

void override_log_level(LogLevel lvl) {
    Level = lvl;
}

unsigned int color(LogLevel log) {
    switch(log) {
        case LOG_ERR: return 31;
        case LOG_INFO: return 32;
        case LOG_WARN: return 33;
        case LOG_DEBUG: return 35;
    }

    return 0;
}

int print_level(LogLevel log) {
    int ret = printf("[");

    switch(log) {
        case LOG_ERR: ret += printf("ERR"); break;
        case LOG_WARN: ret += printf("WARN"); break;
        case LOG_INFO: ret += printf("INFO"); break;
        case LOG_DEBUG: ret += printf("DEBUG"); break; 
    }

    return ret + printf("] ");
}

int println(LogLevel lvl, const char* __restrict__ __format, ...) {
    if (lvl < Level) return 0;

    va_list args;
    va_start(args, __format);

    int ret = printf("\033[%dm", color(lvl));
    ret += print_level(lvl);
    ret += vprintf(__format, args);
    va_end(args);

    ret += printf("\033[0m\n");
    return ret;
}

int print_n(LogLevel lvl, int n) {
    return println(lvl, "%d", n);
}

int print_str(LogLevel lvl, char* str) {
    return println(lvl, "%s", str);
}