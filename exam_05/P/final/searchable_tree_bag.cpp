#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag()
{}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &other) : tree_bag(other)
{}
searchable_tree_bag &searchable_tree_bag::operator=(const searchable_tree_bag &other)
{
    if(this != &other)
        tree_bag::operator=(other);
    return *this;
}
searchable_tree_bag::~searchable_tree_bag()
{}

bool searchable_tree_bag::has(int item) const
{
    node *search = tree;

    while (search)
    {
        if(item == search->value)
            return true;
        else if(item < search->value)
            search = search->l;
        else
            search = search->r;
    }
    return false;
}
