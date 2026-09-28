#include <assert.h>
#include <stdio.h>

#include "util/include/print.h"
#include "util/include/str.h"

int main() {
    Str s = str_from_static("hello");
    Str s2 = str_from_static("helli");

    assert(!str_equals(s, s2));

    s2 = str_from_static("hel");
    assert(!str_equals(s, s2));

    str_concat(&s2, "lo", 2);
    assert(str_equals(s, s2));

    str_free(s); str_free(s2);
    println(LOG_INFO, "Test passed : Str::equals");

    return 0;
}