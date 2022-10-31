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
#include <vector>

using namespace std;

// oh god, a global variable
int failures = 0;

#define ASSERT(thing, message) assert(__LINE__, thing, message)
static inline void assert(size_t line, bool thing, const char* message) {
	if (!thing) {
		cerr << "\e[31mfailure\e[0m (line " << line
		     << "): " << message << '\n';
		++failures;
	}
}

int main() {
	size_t capacity = 7;
	heap test_heap(capacity);
	char addresses[1];

	// ensure that we can insert seven things
	ASSERT(
		test_heap.insert("0", 0, addresses) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("9", 9, addresses + 9) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("-2", -2, addresses - 2) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("7", 7, addresses + 7) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("6", 6, addresses + 6) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("3", 3, addresses + 3) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("2", 2, addresses + 2) == heap::success,
		"could not insert into heap"
	);

	// ensure that we cannot insert another
	ASSERT(
		test_heap.insert("-71", -71, addresses - 71) == heap::heap_full,
		"could still insert into heap!"
	);

	// see about removing something specific
	string id;
	int key = 0;
	char* data = nullptr;
	ASSERT(
		test_heap.remove("9", &key, &data) == heap::success,
		"remove() did not report success"
	);
	ASSERT(key == 9, "wrong key returned");
	ASSERT(data == addresses + 9, "wrong data returned");

	// see if we can perform a deleteMin and get everything back
	ASSERT(
		test_heap.deleteMin(&id, &key, &data) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "-2", "wrong id returned");
	ASSERT(key == -2, "wrong key returned");
	ASSERT(data == addresses - 2, "wrong data returned");



	// ensure we can't insert a duplicate id
	ASSERT(
		test_heap.insert("7", 83, addresses + 83) == heap::id_exists,
		"insert() allowed a duplicate key!"
	);

	// ensure we empty out the heap in the right order
	ASSERT(
		test_heap.deleteMin(&id) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "0", "wrong id returned");
	ASSERT(
		test_heap.deleteMin(&id) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "2", "wrong id returned");
	ASSERT(
		test_heap.deleteMin(&id) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "3", "wrong id returned");
	ASSERT(
		test_heap.deleteMin(&id) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "6", "wrong id returned");
	ASSERT(
		test_heap.deleteMin(&id) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "7", "wrong id returned");

	// ensure that the heap reads as empty
	ASSERT(
		test_heap.deleteMin() == heap::heap_empty,
		"deleteMin() should have reported empty"
	);


	// see if we can change the order by setting a key
	test_heap.insert("second", -12, nullptr);
	test_heap.insert("first", -6, nullptr);
	ASSERT(
		test_heap.setKey("third", 63) == heap::no_such_id,
		"setKey() allowed setting a nonexistent key!"
	);
	ASSERT(
		test_heap.setKey("second", 63) == heap::success,
		"setKey() did not report success"
	);
	test_heap.deleteMin(&id);
	ASSERT(id == "first", "heap order didn't change?");

	return failures;
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
