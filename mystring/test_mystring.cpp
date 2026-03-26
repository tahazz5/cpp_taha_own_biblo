#include <cassert>
#include <iostream>
#include <cstring>

#include "mystring.hpp"

int main() {
    mystring s;
    assert(s.size() == 0);
    assert(std::strcmp(s.c_str(), "") == 0);

    mystring s2("hello");
    assert(s2.size() == 5);
    assert(std::strcmp(s2.c_str(), "hello") == 0);
    assert(s2[0] == 'h');
    assert(s2[4] == 'o');

    mystring s3 = s2;
    assert(s3.size() == 5);
    assert(std::strcmp(s3.c_str(), "hello") == 0);

    mystring s4 = std::move(s2);
    assert(s4.size() == 5);
    assert(std::strcmp(s4.c_str(), "hello") == 0);
    assert(s2.size() == 0);  // moved from

    s.append("world");
    assert(s.size() == 5);
    assert(std::strcmp(s.c_str(), "world") == 0);

    s.append("!");
    assert(s.size() == 6);
    assert(std::strcmp(s.c_str(), "world!") == 0);

    mystring s5("test");
    s5 = s3;
    assert(std::strcmp(s5.c_str(), "hello") == 0);

    mystring s6("move");
    s6 = std::move(s5);
    assert(std::strcmp(s6.c_str(), "hello") == 0);
    assert(s5.size() == 0);

    std::cout << "mystring tests passed\n";
    return 0;
}