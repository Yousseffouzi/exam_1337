#pragma once

#include "bag.hpp"
#include "searchable_bag.hpp"

class set
{
  searchable_bag &s_bag;
  set();
public:
  set &operator=(const set &) = delete;
  set(const set &) = delete;
  set(searchable_bag &);
  ~set();

  bool has(int) const;
  void insert(int);
  void insert(int *, int);
  void print() const;
  void clear();

  searchable_bag &get_bag();
};
