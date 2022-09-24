/* Simple program to run a few heap-related tests, so I can be relatively sure
 * that everything works.
 *
 * I didn't feel like spooling up a full-on testing framework for this, so
 * this'll have to do.
 */

#include "heap/heap.h"
#include <cstddef>
//#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

#define ASSERT(thing, message) assert(__LINE__, thing, message)
static inline void assert(size_t line, bool thing, const char* message) {
	if (!thing) {
		cerr << "\e[31mfailure\e[0m (line " << line
		     << "): " << message << '\n';
		//exit(line);
	}
}

int main() {
	size_t capacity = 5;
	heap test_heap(capacity);
	char addresses[32];

	// ensure that we can insert three things
	ASSERT(
		test_heap.insert("first", 19, addresses) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("second", 66, addresses + 1) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("third", -12, addresses + 2) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("fourth", -12, addresses + 3) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("fifth", 127, addresses + 4) == heap::success,
		"could not insert into heap"
	);

	// ensure that we cannot insert another
	ASSERT(
		test_heap.insert("sixth", -71, addresses  + 5) == heap::heap_full,
		"could still insert into heap!"
	);

	// see if we can perform a deleteMin and get everything back
	std::string id;
	int key = 0;
	char* data = addresses - 1;
	ASSERT(
		test_heap.deleteMin(&id, &key, &data) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "third", "wrong id returned");
	ASSERT(key == -12, "wrong key returned");
	ASSERT(data == addresses + 2, "wrong data returned");

	// see about removing something specific
	ASSERT(
		test_heap.remove("first", &key, &data) == heap::success,
		"remove() did not report success"
	);
	ASSERT(key == 19, "wrong key returned");
	ASSERT(data == addresses, "wrong data returned");

	// ensure we can't insert a duplicate id
	ASSERT(
		test_heap.insert("second", 83, addresses + 5) == heap::id_exists,
		"insert() allowed a duplicate key!"
	);

	// see if we can change the order by setting a key
	ASSERT(
		test_heap.setKey("sixth", -188) == heap::no_such_id,
		"setKey() allowed setting a nonexistent key!"
	);
	ASSERT(
		test_heap.setKey("fifth", -188) == heap::success,
		"setKey() did not report success"
	);

	// ensure we empty out the heap in the right order
	ASSERT(
		test_heap.deleteMin(&id) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "fifth", "wrong id returned");
	ASSERT(
		test_heap.deleteMin(&id) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "fourth", "wrong id returned");
	ASSERT(
		test_heap.deleteMin(&id) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "second", "wrong id returned");

	// ensure that the heap reads as empty
	ASSERT(
		test_heap.deleteMin() == heap::heap_empty,
		"deleteMin() should have reported empty"
	);

	return 0;
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
