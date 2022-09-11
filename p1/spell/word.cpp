#include "spell/word.h"

#include <cctype>
#include <sstream>

std::istream& Word::operator>>(std::istream& is) {
	char c;
	std::ostringstream in_progress;

	while (is.get(c)) {
		if (Word::is_valid_char(c)) in_progress << c;
		else break;
	}

	this->word = in_progress.str();
}

static bool Word::is_valid_char(char c) {
	const char lower = tolower(c);
	return (lower >= 'a' && lower <= 'z') // letter
		   || (c >= '0' && c <= '9') // digit
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
