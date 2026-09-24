#include <assert.h>
#include <stdio.h>
#include "util/include/str.h"

void test_equals() {
    Str s = str_from_static("hello");
    Str s2 = str_from_static("helli");

    assert(!str_equals(s, s2));

    s2 = str_from_static("hel");
    assert(!str_equals(s, s2));

    str_concat(&s, "lo", 2);
    assert(str_equals(s, s2));

    str_free(s); str_free(s2);
    printf("Test passed : Str::equals");
}

int main() {
    test_equals();

    return 0;
}