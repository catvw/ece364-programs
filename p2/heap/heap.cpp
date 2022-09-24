#include "heap.h"

using namespace std;

heap::heap(size_t capacity)
: capacity{capacity},
  filled{0},
  elements(capacity + 1), // because we don't use address 0
  element_table(capacity) {}

heap::code heap::insert(const std::string& id, int key, void* data) {
	// make sure we can actually insert this thing
	if (filled == capacity) return heap::heap_full;
	if (element_table.contains(id)) return heap::id_exists;

	// open up a space in the heap for the new element
	size_t address = percolateUp(key);

	// store the element in both the heap and the table
	auto& e = elements[address];
	e.id = id;
	e.key = key;
	e.data = data;
	element_table.insert(id, static_cast<void*>(&e));

	return heap::success;
}

heap::code heap::setKey(const std::string& id, int key) {
	return heap::success;
}

heap::code heap::deleteMin(std::string* id_ptr, int* key_ptr, void* data_ptr) {
	return heap::success;
}

heap::code heap::remove(const std::string& id, int* key_ptr, void* data_ptr) {
	return heap::success;
}

size_t heap::percolateUp(int key) {
	// don't call this if we're out of free space!
	size_t address = ++filled;

	while (address > 1) {
		auto& child = elements[address];
		auto& parent = elements[address/2];

		if (parent.key > key) {
			// move parent to child and keep looking
			child = parent;
		} else break; // we found our spot!

		address /= 2;
	}

	return address;
}

/*
Copyright (C) 2022  Catherine Van West

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
