#include "checker.h"

#include <sstream>

checker::checker()
: max_word_length{-1} {}

checker::checker(const std::string& wordlist)
: max_word_length{-1} {
	add_words(wordlist);
}

void checker::add_words(const std::string& wordlist) {
	std::istringstream list_in(wordlist);
	std::string line;
	bool more_lines = true;

	while (more_lines) {
		more_lines = !std::getline(list_in, line).fail();
		
		// only add words that meet spec
		try {
			dict.add_word(word{line});
		} catch (invalid_char&) {}
	}
}

std::string checker::check(const std::string& document) {
	std::istringstream doc_in(document);
	std::ostringstream objections;

	bool more_lines = true;
	size_t line_number = 1; // probably start from 1?

	// go through the input line-by-line and check each one
	std::string line;
	while (more_lines) {
		more_lines = !std::getline(doc_in, line).fail();

		std::istringstream line_in(line);
		word w;
		bool more_words = true;
		while (more_words) {
			more_words = !(line_in >> w).fail();
			object_to(w, line_number, objections);
		}

		++line_number;
	}

	return objections.str();
}

void checker::set_max_word_length(ssize_t length) {
	max_word_length = length;
}

void checker::object_to(const word& w, size_t line, std::ostream& obj) {
	if (w.contains_digit()) return; // it's weird, don't bother

	if (max_word_length >= 0 && w.str().length() > max_word_length) {
		obj << "Long word at line " << line
		    << ", starts: " << w.str().substr(0, max_word_length)
		    << '\n';
	} else if (!dict.contains(w)) {
		obj << "Unknown word at line " << line
		    << ": " << w.str()
		    << '\n';
	}
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
