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
	// make sure we can delete something
	if (filled == 0) return heap::heap_empty;

	// actually remove the element & copy out fields
	auto e = percolateDown();
	element_table.remove(e.id);
	if (id_ptr) *id_ptr = e.id;
	if (key_ptr) *key_ptr = e.key;
	if (data_ptr) *static_cast<void**>(data_ptr) = e.data;

	return heap::success;
}

heap::code heap::remove(const std::string& id, int* key_ptr, void* data_ptr) {
	// ensure we have an item that matches
	if (!element_table.contains(id)) return heap::no_such_id;

	// extract the item we need
	ptrdiff_t address = static_cast<element*>(element_table.getPointer(id))
	                    - &elements[0];
	auto e = percolateDown(address);
	element_table.remove(e.id);

	// copy it out and return it
	if (key_ptr) *key_ptr = e.key;
	if (data_ptr) *static_cast<void**>(data_ptr) = e.data;
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
			element_table.setPointer(parent.id, &child);
		} else break; // we found our spot!

		address /= 2;
	}

	return address;
}

heap::element heap::percolateDown(ptrdiff_t address) {
	auto root = elements[address];
	auto& last = elements[filled];

	while (address <= filled/2) {
		auto& parent = elements[address];
		auto& left = elements[address*2];
		auto& right = elements[address*2 + 1];

		auto* swap_with = &left;
		size_t next_address = address*2;

		if (address*2 + 1 <= filled && right.key < left.key) {
			// both addresses are valid and the rightmost one should move
			swap_with = &right;
			++next_address;
		}

		// now, see if we should actually move it
		if (last.key > swap_with->key) {
			parent = *swap_with;
			element_table.setPointer(swap_with->id, &parent);
			address = next_address;
		} else {
			break;
		}
	}

	// insert the last element where we left off
	elements[address] = last;
	element_table.setPointer(last.id, &elements[address]);
	--filled;
	return root;
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
