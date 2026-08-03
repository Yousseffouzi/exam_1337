#pragma once
#include "searchable_bag.hpp"

class set {
private:
	searchable_bag& bag;
	set();
public:
	set(searchable_bag& b) : bag(b){}
	set(const set& other) : bag(other.bag) {}
	set& operator=(const set& other) { (void)other; return *this;}
	~set() {}

	void insert(int value) { if (!(bag.has(value))) bag.insert(value);}
	void insert(int *items, int count) {
		for (int i = 0; i < count ; i++) {
			if (!(bag.has(items[i])))  bag.insert(items[i]);
		}
	}
	void print() const { bag.print(); }
	void clear() { bag.clear(); }
	searchable_bag& get_bag() const { return bag; }
	bool has(int item) const {return bag.has(item); }

};
