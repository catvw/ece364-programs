#include "word.h"

#include <cctype>
#include <sstream>

std::istream& operator>>(std::istream& is, word& w) {
	char c;
	std::ostringstream in_progress;
	w.there_is_a_digit = false;

	while (is.get(c)) {
		if (word::is_valid_char(c)) {
			in_progress << c;
			if (isdigit(c)) w.there_is_a_digit = true;
		}
		else break;
	}

	w.word_str = in_progress.str();
	return is;
}

bool word::is_valid_char(char c) {
	return isalnum(c) // letter
		   || isdigit(c) // digit
		   || c == '-' || c == '\''; // other
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
