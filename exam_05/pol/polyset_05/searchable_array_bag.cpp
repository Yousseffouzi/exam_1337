#include "searchable_array_bag.hpp"
#include "algorithm"

searchable_array_bag::searchable_array_bag()
{}

searchable_array_bag::searchable_array_bag(const searchable_array_bag &other): array_bag(other)
{}

searchable_array_bag &searchable_array_bag::operator=(const searchable_array_bag &other)
{
    array_bag::operator=(other);
    (void)other;
    return *this;
}

searchable_array_bag::~searchable_array_bag()
{}

bool searchable_array_bag::has(int item) const
{
    int *res = std::find(data, data + size, item);
    if (res != data + size)
        return true;
    return false;
}
