#ifndef SEARCHABLE_ARRAY_BAG_HPP
#define SEARCHABLE_ARRAY_BAG_HPP

#include "provided/array_bag.hpp"
#include "provided/searchable_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag {
public:
    searchable_array_bag() {}
    searchable_array_bag(const searchable_array_bag& src) : array_bag(src), searchable_bag(src) {}
    searchable_array_bag& operator=(const searchable_array_bag& src) {
        if (this != &src) array_bag::operator=(src);
        return *this;
    }
    ~searchable_array_bag() {}

    bool has(int item) const {
        for (int i = 0; i < size; i++)
			if (data[i] == item) return true;
        return false;
    }
};

#endif
