#include <assert.h>
#include <stdio.h>

#include "util/include/print.h"
#include "util/include/str.h"

// test Valgrind errors
void test_print() {
    Str s = str_from_static("");
    println(LOG_DEBUG, "Length 0 : -%s-", s.value);

    str_push(&s, 'h');
    println(LOG_DEBUG, "Length 1 : -%s-", s.value);

    str_push(&s, 'e');
    println(LOG_DEBUG, "Length 2 : -%s-", s.value);

    str_push(&s, 'l');
    println(LOG_DEBUG, "Length 3 : -%s-", s.value);

    println(LOG_INFO, "Test passed : Str::print");    
}

void test_equals() {
    Str s = str_from_static("hello");
    Str s2 = str_from_static("helli");

    assert(!str_equals(s, s2));

    s2 = str_from_static("hel");
    assert(!str_equals(s, s2));

    str_concat(&s2, "lo", 2);
    assert(str_equals(s, s2));

    str_free(s); str_free(s2);
    println(LOG_INFO, "Test passed : Str::equals");
}

void test_index_of() {
    assert(str_index_of(str_from_static("GET"), NULL, 1) == -1);
    assert(str_index_of(str_from_static("GET"), "GET", 0) == -1);
    assert(str_index_of(str_from_static("GET"), "GET", 3) == 0);
    assert(str_index_of(str_from_static("__GET__"), "GET", 3) == 2);
    assert(str_index_of(str_from_static("GEGET"), "GET", 3) == 2);
    assert(str_index_of(str_from_static("GEOGET"), "GET", 3) == 3);
    assert(str_index_of(str_from_static("LAST ONE !!"), "GET", 3) == -1);

    println(LOG_INFO, "Test passed : Str::index_of");
}

void test_split() {
    Str get = str_from_static("GET");
    Split s = str_split(get, "!", 1);
    
    assert(s.length == 1);
    assert(str_equals(get, s.values[0]));
    split_free(s);

    Str test = str_from_static("GET!");
    s = str_split(test, "!", 1);
    assert(s.length == 2);
    assert(str_equals(get, s.values[0]));
    assert(str_equals(str_new(), s.values[1]));
    split_free(s);

    test = str_from_static("GET!GET!");
    s = str_split(test, "!", 1);
    assert(s.length == 3);
    assert(str_equals(get, s.values[0]));
    assert(str_equals(get, s.values[1]));
    assert(str_equals(str_new(), s.values[2]));
    split_free(s);

    println(LOG_INFO, "Test passed : Str::split");
}

int main() {
    override_log_level(LOG_DEBUG);

    test_print();
    test_equals();
    test_index_of();
    test_split();

    return 0;
}