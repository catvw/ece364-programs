/* Word class for the spellchecker, so that I can easily work with them. */

#ifndef WORD_H
#define WORD_H

#include <string>
#include <istream>

class word {
public:
	/* Create a new word. */
	inline word() : word_str{}, there_is_a_digit{false} {}

	/* Return whether the given character is a valid character for a word. */
	static bool is_valid_char(char);

	/* Return the string representation of the word. */
	inline const std::string& str() const { return word_str; }

	/* Check if the word contains a digit. */
	inline const bool contains_digit() const { return there_is_a_digit; }

	friend std::istream& operator>>(std::istream&, word&);

private:
	std::string word_str;
	bool there_is_a_digit;
};

/* Read a word from a stream. Will stop reading when a word separator is
   encountered or EOF is reached. */
std::istream& operator>>(std::istream&, word&);

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
