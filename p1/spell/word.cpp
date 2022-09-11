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
