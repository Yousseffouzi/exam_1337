#pragma once

#include "searchable_bag.hpp"

class set
{
    searchable_bag &bag;
public:
    set(const set &other);
    set(searchable_bag &bag);
    ~set();

    void insert(int item);
    void insert(int *item, int count);
    void clear();
    void print() const;

    bool has(int item) const;
    searchable_bag &get_bag() const;
};

