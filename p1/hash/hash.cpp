/* Since some part of me wants to leave your header *exactly* as you wrote it,
   I'll put all my stuff in here. I'm not all that crazy about how the
   interface is set up, and think it could use more helper functions... but so
   be it. Backend magic for now. */

#include "hash.h"

#include "primes.h"
#include <functional>
#include <utility>

constexpr const float load_factor = .75;
const std::hash<std::string> string_hash;

namespace code {
enum {
	success = 0,

	// for insert()
	key_exists = 1,
	rehash_failed = 2,

	// for setPointer()
	no_such_key = 1,

	// for findPos()
	not_in_table = -1, // unsurprisingly
};
} /* ~return_code */

/* Seek out a prospective position in the table. The value returned by this
   function is either the index in the table where the given key was found *or*
   the empty cell to put the key in.

   Note: there better be a position that this can find! */
template<typename Cell>
int seek(const std::vector<Cell>& data, const std::string& key) {
	auto location = string_hash(key);
	int index;
	bool should_stop;

	do {
		index = location++ % data.size();
		const Cell& cell = data[index];

		/* we should stop if we either find an empty (non-deleted) cell or find
		   a matching key */
		should_stop = !cell.isOccupied || (!cell.isDeleted && cell.key == key);
	} while (!should_stop);

	return index;
}

/* Set up the given cell to contain an item. */
template<typename Cell>
void set(Cell& cell, const std::string& key, void* pv) {
	cell.key = key;
	cell.pv = pv;
	cell.isOccupied = true;
}

/* Lazily delete the given cell. */
template<typename Cell>
void del(Cell& cell) {
	cell.isDeleted = true;
}

hashTable::hashTable(int size)
: filled{0},
  capacity{static_cast<int>(hashTable::getPrime(size))},
  data(capacity) {}

int hashTable::insert(const std::string& key, void* pv) {
	// ensure that we have the space
	if (static_cast<float>(filled)/capacity > load_factor) {
		if (!rehash()) return code::rehash_failed;
	}

	// find the prospective location
	int location = seek(data, key);
	hashItem& cell = data[location];

	if (cell.isOccupied) { // this key is already here
		return code::key_exists;
	}

	set(cell, key, pv);
	++filled;
	return code::success;
}

bool hashTable::contains(const std::string& key) {
	return findPos(key) != code::not_in_table;
}

void* hashTable::getPointer(const std::string& key, bool* b) {
	const int index = findPos(key);
	const bool found = index != code::not_in_table;

	// set the passed pointer if it's valid
	if (b) *b = found;

	if (found) return data[index].pv;
	else return nullptr;
}

int hashTable::setPointer(const std::string& key, void* pv) {
	const int index = findPos(key);
	if (index == code::not_in_table) return code::no_such_key;

	data[index].pv = pv;
	return code::success;
}

bool hashTable::remove(const std::string& key) {
	const int index = findPos(key);
	if (index == code::not_in_table) return false;

	del(data[index]);
	return true;
}

int hashTable::hash(const std::string& key) {
	return string_hash(key) % capacity; // not that I ever use this, but
}

int hashTable::findPos(const std::string& key) {
	const int index = seek(data, key);
	if (data[index].isOccupied) return index;
	else return code::not_in_table;
}

bool hashTable::rehash() {
	int next_prime = getPrime(capacity);

	try { // I'm going to assume that memory is cheaper than time
		// create a new (temporary) hash table with the new size
		hashTable new_table(next_prime);

		// loop through everything and insert what matters
		for (auto& cell : data) {
			const bool should_keep = cell.isOccupied && !cell.isDeleted;
			if (should_keep) new_table.insert(cell.key, cell.pv);
		}

		// get the data out of the old table
		capacity = new_table.capacity;
		data = std::move(new_table.data);
		return true;
	} catch (std::bad_alloc&) { // I was wrong!
		return false;
	}
}

unsigned int hashTable::getPrime(int size) {
	return next_prime(size); // why is this a function in the table itself?
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
