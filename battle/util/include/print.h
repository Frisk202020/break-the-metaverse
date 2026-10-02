#include <stdarg.h>
#include <stdio.h>

typedef enum log {
    LOG_DEBUG,
    LOG_WARN,
    LOG_INFO,
    LOG_ERR
} LogLevel;

void override_log_level(LogLevel lvl);
int println(LogLevel lvl, const char* __restrict__ __format, ...);
int print_n(LogLevel lvl, int n);
int print_str(LogLevel lvl, char* str);