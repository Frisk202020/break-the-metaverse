#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "util/include/str.h"
#include "util/include/print.h"

Str str_new() {
    return (Str) {
        "\0", 0, 0, true
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
        newBuff[s->length] = '\0';

        if (!s->__static) free(s->value);

        s->__static = false;
        s->value = newBuff;
    }

    s->value[s->length] = c; 
    s->length++;
    s->value[s->length] = '\0';
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

int str_index_of_from(Str test, char* target, unsigned target_len, unsigned start) {
    if (target == NULL || target_len == 0) {
        println(LOG_WARN, "Queried str_index_of with empty target");
        return -1;
    }

    unsigned end_index = target_len - 1;
    int currentIndex = 0;

    for (int i = 0; i < test.length; i++) {
        if (test.value[i] == target[currentIndex]) {
            if (currentIndex == end_index) return i - end_index;
            currentIndex++;
            continue;
        }

        currentIndex = test.value[i] == target[0] ? 1 : 0;
    }

    return -1;
}

int str_index_of(Str test, char* target, unsigned target_len) { 
    return str_index_of_from(test, target, target_len, 0); 
}

Split split_empty() { return (Split) { NULL, 0 }; }

Split str_split(Str test, char* sep, unsigned sep_len) {
    Split ret = {
        malloc(test.length * sizeof(Str)),
        1
    };
    ret.values[0] = str_new();

    Str buf = str_new();
    for (int i = 0; i < test.length; i++) {
        if (test.value[i] == sep[buf.length]) {
            if (buf.length == sep_len - 1) {
                ret.values[ret.length] = str_new();
                ret.length++;
                str_clear(&buf);
            } else {
                str_push(&buf, test.value[i]);
            }

            continue;
        }

        unsigned id = ret.length - 1;
        str_concat(&ret.values[id], buf.value, buf.length);

        str_clear(&buf);
        str_push(&ret.values[id], test.value[i]);
    }

    str_free(buf);
    return ret;
}

void split_free(Split s) {
    for (int i = 0; i < s.length; i++) {
        str_free(s.values[i]);
    }
}