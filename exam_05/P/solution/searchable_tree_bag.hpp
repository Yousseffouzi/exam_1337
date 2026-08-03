#pragma once

#include "../polyset_sub/tree_bag.hpp"
#include "../polyset_sub/searchable_bag.hpp"

class searchable_tree_bag : public tree_bag , public searchable_bag
{
    public:
        searchable_tree_bag();
        searchable_tree_bag(const searchable_tree_bag &);
        searchable_tree_bag &operator=(const searchable_tree_bag &other);
        ~searchable_tree_bag();
        bool has(int item) const;
};