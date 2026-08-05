#include "set.hpp"
        
set::set(const set &other) : bag(other.bag)
{}

set::set(searchable_bag &b): bag(b)
{}

set::~set()
{}

void set::insert(int item)
{
    if(!bag.has(item))
        bag.insert(item);
}
void set::insert(int *item, int count)
{
    for (int i = 0; i < count; i++)
    {
        if(!bag.has(item[i]))
        bag.insert(item[i]);
    }
}
void set::print() const
{
    bag.print();
}
void set::clear()
{
    bag.clear();
}

const searchable_bag &set::get_bag() const
{
    return bag;
}

bool set::has(int item) const
{
    return (bag.has(item));
}
