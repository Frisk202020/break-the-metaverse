#include <stdarg.h>
#include <stdio.h>

typedef enum log {
    LOG_ERR,
    LOG_WARN,
    LOG_INFO
} LogLevel;

int println(LogLevel lvl, const char* __restrict__ __format, ...);