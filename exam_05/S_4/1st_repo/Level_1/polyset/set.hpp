#ifndef SET_HPP
#define SET_HPP

#include "provided/searchable_bag.hpp"

class set {
    searchable_bag& _bag;
public:
    set(searchable_bag& b) : _bag(b) {}
    set(const set& src) : _bag(src._bag) {}
    set& operator=(const set& src) {
        if (this != &src) _bag = src._bag;
        return *this;
    }
    ~set() {}

    void insert(int item) { if (!_bag.has(item)) _bag.insert(item); }
    void insert(int* items, int count) { for (int i = 0; i < count; i++) insert(items[i]); }
    bool has(int item) const { return _bag.has(item); }
    void print() const { _bag.print(); }
    void clear() { _bag.clear(); }
    searchable_bag& get_bag() { return _bag; }
    const searchable_bag& get_bag() const { return _bag; }
};

#endif
