#ifndef SEARCHABLE_TREE_BAG_HPP
#define SEARCHABLE_TREE_BAG_HPP

#include "provided/tree_bag.hpp"
#include "provided/searchable_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag {
public:
    searchable_tree_bag() {}
    searchable_tree_bag(const searchable_tree_bag& src) : tree_bag(src), searchable_bag(src) {}
    searchable_tree_bag& operator=(const searchable_tree_bag& src) {
        if (this != &src) tree_bag::operator=(src);
        return *this;
    }
    ~searchable_tree_bag() {}

    bool has(int item) const {
        for (node* current = tree; current; current = (item < current->value) ? current->l : current->r)
            if (item == current->value) return true;
        return false;
    }
};

#endif
