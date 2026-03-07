#include <iostream>
#include "shared_pointer.hpp"

struct Test {
    int val;
    Test(int v) : val(v) { std::cout << "Test " << val << " created\n"; }
    ~Test() { std::cout << "Test " << val << " destroyed\n"; }
};

int main() {
    std::cout << "--- Test 1: Construction ---\n";
    shared_pointer<Test> sp1(new Test(1));
    std::cout << "sp1 created\n";

    std::cout << "\n--- Test 2: Copy Constructor ---\n";
    shared_pointer<Test> sp2 = sp1;
    std::cout << "sp2 copied from sp1\n";

    std::cout << "\n--- Test 3: Move Constructor ---\n";
    shared_pointer<Test> sp3 = std::move(sp1);
    std::cout << "sp3 moved from sp1\n";
    std::cout << "sp1 should be nullptr now\n";

    std::cout << "\n--- Test 4: Copy Assignment ---\n";
    shared_pointer<Test> sp4;
    sp4 = sp2;
    std::cout << "sp4 assigned from sp2\n";

    std::cout << "\n--- Test 5: Move Assignment ---\n";
    shared_pointer<Test> sp5;
    sp5 = std::move(sp2);
    std::cout << "sp5 moved from sp2\n";
    std::cout << "sp2 should be nullptr now\n";

    std::cout << "\n--- Test 6: Multiple Copies & Destruction ---\n";
    {
        shared_pointer<Test> sp6(new Test(2));
        shared_pointer<Test> sp7 = sp6;
        shared_pointer<Test> sp8 = sp7;
        std::cout << "sp6, sp7, sp8 pointing to same Test(2)\n";
    } // destruction automatique ici

    std::cout << "\n--- End of main ---\n";
    return 0;
}