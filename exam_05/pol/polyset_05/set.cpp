#include "set.hpp"
#include <iostream>

set::set(searchable_bag &src): s_bag(src)
{}

set::~set()
{}

void set::insert(int item) 
{
	if (!s_bag.has(item))
		s_bag.insert(item);
}

void set::insert(int *items, int count) {
	for (int i = 0; i < count; i++)
	{
		s_bag.insert(items[i]);
	}
}

void set::print() const {
	s_bag.print();
}

void set::clear() {
	s_bag.clear();
}

searchable_bag &set::get_bag()
{
	return s_bag;
}


bool set::has(int item) const
{
	return s_bag.has(item);
}
