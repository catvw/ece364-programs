/* Public-facing interface for my binary heap class. Pretty much based on your
 * specifications. Pretty much. More or less...
 */

#ifndef HEAP_H
#define HEAP_H

#include <cstddef>
#include <string>

/* This is actually a *binary* heap, but hey -- I didn't write the interface.
 * So don't ask me.
 */
class heap {
public:
	/* Error codes used by heap functions, because apparently we're not allowed
	 * to throw exceptions.
	 */
	enum code {
		success = 0,

		// used by insert()
		heap_full = 1,
		id_exists = 2,

		// used by setKey() & remove()
		no_such_id = 1,

		// used by deleteMin()
		heap_empty = 1,
	};

	/* Construct a heap with the given capacity.
	 *
	 * Yes, I made the argument a size_t.
	 */
	heap(std::size_t size);

	/* Insert a new node into the binary heap with the given id, key (used for
	 * priority ordering), and optional pointer to data.
	 */
	code insert(const std::string& id, int key, void* data = nullptr);

	/* Set the key of a given node to the given value, by node id.
	 */
	code setKey(const std::string& id, int key);

	/* Find the node with the smallest key and remove it from the heap. If any
	 * of the optional pointers are supplied, the associated field in the
	 * deleted node will be copied to them.
	 *
	 * data_ptr should really have type void**, but this was the interface, so
	 * here it is. I might also have put these in a different order, as well,
	 * given how default parameters behave, but whatever...
	 */
	code deleteMin(std::string* id_ptr = nullptr,
	               int* key_ptr = nullptr,
	               void* data_ptr = nullptr);

	/* Remove the node with the given id from the binary heap. See deleteMin()
	 * for how the two subsequent pointers are used.
	 */
	code remove(const std::string& id,
	            int* key_ptr = nullptr,
	            void* data_ptr = nullptr);
};

#endif

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
