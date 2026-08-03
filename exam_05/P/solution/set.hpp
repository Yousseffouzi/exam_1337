#pragma once

#include "../polyset_sub/searchable_bag.hpp"

class set
{
    private:
        searchable_bag &bag;
    public:
    set();
    ~set();
    set(searchable_bag &other);
    set &operator=(set &other);
    void insert (int);
	void insert (int *, int);
	void print() const;
	void clear();
    bool has(int item) const;
    searchable_bag &get_bag();
};