#include "heap.h"

using namespace std;

heap::heap(size_t capacity)
: capacity{capacity},
  filled{0},
  elements(capacity + 1), // because we don't use address 0
  element_table(capacity) {}

heap::code heap::insert(const string& id, int key, void* data) {
	// make sure we can actually insert this thing
	if (filled == capacity) return heap::heap_full;
	if (element_table.contains(id)) return heap::id_exists;

	// open up a space in the heap for the new element, starting at the new end
	size_t address = percolateUp(key, ++filled);

	// store the element in both the heap and the table
	auto& e = elements[address];
	e.id = id;
	e.key = key;
	e.data = data;
	element_table.insert(id, static_cast<void*>(&e));

	return heap::success;
}

heap::code heap::setKey(const string& id, int key) {
	// remove and re-insert the element with a new key
	void* data;
	heap::code report = remove(id, nullptr, &data);
	if (report == heap::success) insert(id, key, data);
	return report;
}

heap::code heap::deleteMin(string* id_ptr, int* key_ptr, void* data_ptr) {
	// make sure we can delete something
	if (filled == 0) return heap::heap_empty;

	// actually remove the element
	extract(id_ptr, key_ptr, data_ptr);
	return heap::success;
}

heap::code heap::remove(const string& id, int* key_ptr, void* data_ptr) {
	// ensure we have an item that matches
	if (!element_table.contains(id)) return heap::no_such_id;

	// extract the item we need
	ptrdiff_t address = static_cast<element*>(element_table.getPointer(id))
	                    - &elements[0];
	extract(nullptr, key_ptr, data_ptr, address);
	return heap::success;
}

/*
	Thoughts on heap manipulation:

	This would be far more elegant if the hash table owned the elements, and
	the heap just contained pointers to them. One would not have to worry about
	re-inserting elements into the table, which would both simplify the code
	(slightly) and likely improve speed, as there would be far fewer table
	accesses. I imagine you *wanted* us to deal with the headache of keeping
	the table consistent, so that's what I did, but a templatized hash table
	would have allowed for a more efficient, cleaner heap (as well as being
	more in line with C++'s philosophy).
*/

ptrdiff_t heap::percolateUp(int key, ptrdiff_t address) {
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

ptrdiff_t heap::percolateDown(ptrdiff_t address) {
	auto& last = elements[filled]; // the element that needs to move

	while (address <= filled/2) {
		// basically: pretend last is where parent is, and swap accordingly
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

	return address;
}

void heap::extract(string* id_ptr, int* key_ptr,
                   void* data_ptr, ptrdiff_t address) {
	// pull out the element we need
	auto e = elements[address];

	// hang onto the last element in the heap
	auto last = elements[filled];

	/* perform a percolateDown() followed by a percolateUp(), to maintain the
	   heap ordering property, then put the last heap element there */
	address = percolateUp(last.key, percolateDown(address));
	elements[address] = last;
	element_table.setPointer(last.id, &elements[address]);

	element_table.remove(e.id);
	if (id_ptr) *id_ptr = e.id;
	if (key_ptr) *key_ptr = e.key;
	if (data_ptr) *static_cast<void**>(data_ptr) = e.data;
	--filled;
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
