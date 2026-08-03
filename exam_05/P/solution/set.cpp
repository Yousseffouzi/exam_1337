#include "set.hpp"

set::set() : bag(bag)
{
}
set::~set()
{
}
set::set(searchable_bag &other) : bag(other)
{
}
set &set::operator=(set &other)
{
}
void set::insert (int item)
{
    if(!bag.has(item))
    bag.insert(item);
}
void set::insert (int *item, int count)
{
    bag.insert(item, count);
}
void set::print() const
{
    bag.print();
}
void set::clear()
{
    bag.clear();
}
bool set::has(int item) const
{
    return bag.has(item);
}

searchable_bag &set::get_bag()
{
    return bag;
}