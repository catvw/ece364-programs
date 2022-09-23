#include "heap.h"

using namespace std;

heap::heap(size_t size) {}

heap::code heap::insert(const std::string& id, int key, void* data) {
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
