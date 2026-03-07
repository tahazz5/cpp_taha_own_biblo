#include <iostream>
#include "uniquepointer.hpp"

struct Test {
    int x;
    Test(int v) : x(v) {}
    ~Test() { std::cout << "Destructor called for " << x << "\n"; }
};

int main() {
    std::cout << "--- Test 1: Construction & Dereference ---\n";
    uniquepointer<int> p1(new int(10));
    std::cout << (*p1 == 10 ? "Test 1 OK\n" : "Test 1 FAIL\n");

    uniquepointer<Test> t1(new Test(42));
    std::cout << (t1->x == 42 ? "Test 2 OK\n" : "Test 2 FAIL\n");

    std::cout << "--- Test 2: Move Constructor ---\n";
    uniquepointer<int> p2 = std::move(p1);
    std::cout << (p1.get() == nullptr ? "Move Test OK\n" : "Move Test FAIL\n");
    std::cout << (*p2 == 10 ? "Move Value OK\n" : "Move Value FAIL\n");

    std::cout << "--- Test 3: Move Assignment ---\n";
    uniquepointer<int> p3;
    p3 = std::move(p2);
    std::cout << (p2.get() == nullptr && *p3 == 10 ? "Move Assignment OK\n" : "Move Assignment FAIL\n");

    std::cout << "--- Test 4: release() ---\n";
    int* raw = p3.release();
    std::cout << (p3.get() == nullptr && *raw == 10 ? "Release OK\n" : "Release FAIL\n");
    delete raw;

    std::cout << "--- Test 5: reset() ---\n";
    p3.reset(new int(77));
    std::cout << (*p3 == 77 ? "Reset OK\n" : "Reset FAIL\n");

    std::cout << "--- Test 6: Destructor ---\n";
    {
        uniquepointer<Test> t2(new Test(99));
    } // Destructor called here

    return 0;
}