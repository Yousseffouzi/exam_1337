#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag()
{}

searchable_tree_bag::~searchable_tree_bag()
{}

searchable_tree_bag &searchable_tree_bag::operator=(const searchable_tree_bag &other)
{
    tree_bag::operator=(other);
    (void)other;
    return *this;
}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &)
{}

bool searchable_tree_bag::has(int item) const
{
    node *current = tree;
    while (current)
    {
        if (item == current->value)
            return true;
        else if (item < current->value)
            current = current->l;
        else
            current = current->r;
    }    
    return false;
}
