#include "dictionary.h"

dictionary::dictionary()
: words(25000) {}

void dictionary::add_word(const word& w) {
	// you never said what we should do if the rehash fails, so...
	words.insert(w.str(), nullptr);
}

bool dictionary::contains(const word& w) {
	return words.contains(w.str());
}
