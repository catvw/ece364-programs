/* Spellchecker class for the spellchecker. Sort of redundant, but... that's
   what this is. */

#ifndef CHECKER_H
#define CHECKER_H

#include "dictionary.h"
#include "word.h"

#include <cstdint>
#include <string>
#include <ostream>

class checker {
public:
	/* Construct a spellchecker with the given wordlist. Every "word" in the
	   wordlist will be read into the checker's internal dictionary. */
	checker(const std::string&);

	/* Check the given document against the dictionary, and report all the
	   violations. */
	std::string check(const std::string&);

	/* Set the maximum word length to consider a valid word. This does not
	   affect the internal dictionary, so feel free to alter it at will.
	   Negative values will disable length checking.

	   Respectfully, why do we *need* a maximum word length? */
	void set_max_word_length(ssize_t);

private:
	/* Write objections to the given word on the given line to the given
	   stream. */
	void object_to(const word&, size_t, std::ostream&);

	dictionary dict;
	ssize_t max_word_length;
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
