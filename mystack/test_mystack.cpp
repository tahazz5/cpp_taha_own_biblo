#include <cassert>
#include <iostream>
#include <string>
#include <utility>

#include "mystack.hpp"

struct Point {
    int x;
    int y;
};

int main() {
    mystack<int> s;
    assert(s.empty());

    s.push(10);
    s.push(20);
    assert(!s.empty());
    assert(s.size() == 2);
    assert(s.top() == 20);

    s.pop();
    assert(s.top() == 10);

    s.emplace(30);
    assert(s.top() == 30);

    mystack<std::string> names;
    names.push("alpha");
    std::string beta = "beta";
    names.push(std::move(beta));
    assert(names.size() == 2);
    assert(names.top() == "beta");

    mystack<Point> pts;
    pts.emplace(Point{2, 5});
    assert(pts.top().x == 2 && pts.top().y == 5);

    mystack<int> copy = s;
    assert(copy.size() == s.size());
    assert(copy.top() == s.top());

    mystack<int> moved = std::move(copy);
    assert(moved.size() == 2);
    assert(moved.top() == 30);

    std::cout << "mystack tests passed\n";
    return 0;
}
