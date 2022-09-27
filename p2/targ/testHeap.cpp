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
	char addresses[32];

	// ensure that we can insert enough things
	ASSERT(
		test_heap.insert("first", 19, addresses) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("second", -12, addresses + 1) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("third", 5, addresses + 2) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("fourth", 66, addresses + 3) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("fifth", 127, addresses + 4) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("sixth", -6, addresses + 5) == heap::success,
		"could not insert into heap"
	);
	ASSERT(
		test_heap.insert("seventh", 3, addresses + 6) == heap::success,
		"could not insert into heap"
	);

	// ensure that we cannot insert another
	ASSERT(
		test_heap.insert("eighth", -71, addresses  + 7) == heap::heap_full,
		"could still insert into heap!"
	);

	// see if we can perform a deleteMin and get everything back
	string id;
	int key = 0;
	char* data = addresses - 1;
	ASSERT(
		test_heap.deleteMin(&id, &key, &data) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "second", "wrong id returned");
	ASSERT(key == -12, "wrong key returned");
	ASSERT(data == addresses + 1, "wrong data returned");

	// see about removing something specific
	ASSERT(
		test_heap.remove("fourth", &key, &data) == heap::success,
		"remove() did not report success"
	);
	ASSERT(key == 66, "wrong key returned");
	ASSERT(data == addresses + 3, "wrong data returned");


	// ensure we can't insert a duplicate id
	ASSERT(
		test_heap.insert("sixth", 83, addresses + 7) == heap::id_exists,
		"insert() allowed a duplicate key!"
	);

/*
	// see if we can change the order by setting a key
	ASSERT(
		test_heap.setKey("eighth", -188) == heap::no_such_id,
		"setKey() allowed setting a nonexistent key!"
	);
	ASSERT(
		test_heap.setKey("seventh", -188) == heap::success,
		"setKey() did not report success"
	);
*/

	// ensure we empty out the heap in the right order
	ASSERT(
		test_heap.deleteMin(&id) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "sixth", "wrong id returned");
	ASSERT(
		test_heap.deleteMin(&id) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "seventh", "wrong id returned");
	ASSERT(
		test_heap.deleteMin(&id) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "third", "wrong id returned");
	ASSERT(
		test_heap.deleteMin(&id) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "first", "wrong id returned");
	ASSERT(
		test_heap.deleteMin(&id) == heap::success,
		"deleteMin() did not report success"
	);
	ASSERT(id == "fifth", "wrong id returned");

	// ensure that the heap reads as empty
	ASSERT(
		test_heap.deleteMin() == heap::heap_empty,
		"deleteMin() should have reported empty"
	);

	// ensure that this also just functions as a queue
	vector<string> ids {
		"first", "second", "third", "fourth", "fifth"
	};

	for (auto& next : ids) {
		test_heap.insert(next, -1, nullptr);
	}

	for (auto& next : ids) {
		test_heap.deleteMin(&id);
		ASSERT(
			id == next,
			(string("yielded \"") + id + "\", not \""+ next + "\"").c_str()
		);
	}

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
