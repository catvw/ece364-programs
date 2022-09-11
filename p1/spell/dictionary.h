/* Dictionary class for the spellchecker. */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "hash/hashTable.h"
#include "spell/word.h"

class dictionary {
public:
	/* Add a word to the dictionary. */
	void add_word(const word&);

	/* Check if a word is in the dictionary. */
	bool contains(const word&);

private:
	hashTable words;
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
