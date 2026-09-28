#include <stdbool.h>

typedef struct str {
    char* value;
    unsigned int length;
    unsigned int __capacity;
    bool __static;
} Str;

Str str_new();
Str str_from_static(const char* s);
void str_push(Str* s, char c);
void str_concat(Str* s, char* buff, int len);
void str_clear(Str* s);
void str_free(Str s);
bool str_equals(Str s1, Str s2);