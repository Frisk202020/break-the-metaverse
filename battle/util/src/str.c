#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "util/include/str.h"

Str str_new() {
    return (Str) {
        "\0", 0, 0, false
    };
}

Str str_from_static(const char* s) {
    int n = strlen(s);

    return (Str) {
        (char*)s, n, n, true
    };
}

void str_push(Str* s, char c) {
    if (s->length == s->__capacity) {
        s->__capacity = s->__capacity == 0 ? 1 : s->__capacity << 1;
        char* newBuff = malloc((s->__capacity + 1) * sizeof(char));

        for (int i = 0; i < s->length; i++) {
            newBuff[i] = s->value[i];
        } 
        newBuff[s->__capacity] = '\0';

        if (!s->__static) free(s->value);

        s->__static = false;
        s->value = newBuff;
    }

    s->value[s->length] = c; 
    s->length++;
}

void str_concat(Str* s, char* buff, int n) {
    for (int i = 0; i < n; i++) {
        str_push(s, buff[i]);
    }
}

void str_clear(Str* s) {
    str_free(*s);

    s->value = "\0";
    s->length = 0;
    s->__capacity = 0;
    s->__static = true;
}

void str_free(Str s) {
    if (!s.__static) free(s.value);
}

bool str_equals(Str s1, Str s2) {
    if (s1.length != s2.length) return false;

    for (int i = 0; i < s1.length; i++) {
        if (s1.value[i] != s2.value[i]) return false;
    }

    return true;
}

