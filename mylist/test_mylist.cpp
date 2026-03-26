#include <cassert>
#include <iostream>
#include <string>
#include <utility>

#include "mylist.hpp"

struct Point {
    int x;
    int y;
};

int main() {
    mylist<int> l;
    assert(l.empty());
    assert(l.size() == 0);

    l.push_back(10);
    l.push_back(20);
    assert(!l.empty());
    assert(l.size() == 2);
    assert(l.back() == 20);
    assert(l.front() == 10);

    l.push_front(5);
    assert(l.size() == 3);
    assert(l.front() == 5);
    assert(l.back() == 20);

    l.pop_front();
    assert(l.front() == 10);
    assert(l.size() == 2);

    l.pop_back();
    assert(l.back() == 10);
    assert(l.size() == 1);

    l.emplace_back(30);
    assert(l.back() == 30);

    mylist<std::string> names;
    names.push_back("alpha");
    std::string beta = "beta";
    names.push_back(std::move(beta));
    assert(names.size() == 2);
    assert(names.back() == "beta");

    mylist<Point> pts;
    pts.emplace_back(Point{2, 5});
    assert(pts.back().x == 2 && pts.back().y == 5);

    mylist<int> copy = l;
    assert(copy.size() == l.size());
    assert(copy.front() == l.front());

    mylist<int> moved = std::move(copy);
    assert(moved.size() == 2);
    assert(moved.back() == 30);

    std::cout << "mylist tests passed\n";
    return 0;
}