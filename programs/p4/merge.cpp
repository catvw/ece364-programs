#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct character {
	char c;
	size_t orig_pos;
	bool second;
	bool right_rel;
};

string prompt(const char* pr) {
	string dict_file;
	cout << pr;
	getline(cin, dict_file);
	return dict_file;
}

string read_file(istream& file, string& out) {
	// get until EOF, so long as we don't see any null characters
	getline(file, out, '\0');
	return out;
}

/* create a string type with original-position information, so that I can do
   what I do here */
vector<character> create_extra_string(const string& str) {
	vector<character> estr(str.size());
	for (size_t i = 0; i < str.size(); ++i) {
		estr[i].c = str[i];
		estr[i].orig_pos = i;
		estr[i].second = false;
		estr[i].right_rel = false;
	}
	return estr;
}

vector<character*> create_percolate_reference(vector<character>& m) {
	vector<character*> m_ref(m.size());
	for (size_t i = 0; i < m.size(); ++i) {
		m_ref[i] = &m[i];
	}
	return m_ref;
}

/* mark the earliest possible positions that second-string characters could
   occur */
bool mark_seconds(vector<character>& m, const string& sec) {
	size_t sec_i = 0;
	for (size_t i = 0; i < m.size() && sec_i < sec.size(); ++i) {
		if (m[i].c == sec[sec_i]) { // found a match, put it here
			m[i].second = true;
			++sec_i;
		}
	}

	return sec_i == sec.size(); // placed all the characters!
}

/* mark which elements of each string are in the right place relative to
   their end */
void mark_relatively_correct(vector<character>& m,
                             const string& fir,
                             const string& sec) {
	ssize_t fir_i = fir.length() - 1;
	ssize_t sec_i = sec.length() - 1;
	for (size_t i = m.size() - 1; i >= 0 && fir_i >= 0 && sec_i >= 0; --i) {
		if (!m[i].second) {
			m[i].right_rel = m[i].c == fir[fir_i];
			--fir_i;
		} else {
			m[i].right_rel = m[i].c == sec[sec_i];
			--sec_i;
		}
	}
}

void print_it(vector<character>& m) {
	// print out what we got
	cout << "o: ";
	for (size_t i = 0; i < m.size(); ++i) {
		cout << (char) (m[i].second ? m[i].c : toupper(m[i].c));
	}
	cout << '\n';
}

void print_it(vector<character*>& m) {
	// print out what we got
	cout << "r: ";
	for (size_t i = 0; i < m.size(); ++i) {
		cout << (char) (m[i]->second ? m[i]->c : toupper(m[i]->c));
	}
	cout << '\n';
}

/* percolate second characters towards the end of the string */
void percolate(vector<character>& m_orig, const string& fir, const string& sec) {
	const size_t size = m_orig.size();
	vector<character*> m = create_percolate_reference(m_orig);

	bool percolating = true;
	while (percolating) {
		percolating = false;

		// execute a bunch of non-breaking swaps
		for (ssize_t i = size - 2; i >= 0; --i) {
			if (m[i]->second && !m[i + 1]->second && m[i + 1]->c == m[i]->c) {
				m[i]->second = false;
				m[i + 1]->second = true;
				percolating = true;
			}
		}

		print_it(m_orig);
		print_it(m);
		cout << '\n';

		// make a single long-distance swap
		ssize_t last_second = -1;
		ssize_t fir_i = 0;
		for (size_t i = 0; i < fir.size(); ++i) {
			if (m[i]->second) {
				last_second = i;
			} else {
				// first string, so see if it's in the right place
				bool right = fir[fir_i] == m[i]->c;
				if (!right) {
					// the only place the missing character could possibly be
					// is the last second-string block
					const char looking_for = fir[fir_i];

					if (last_second > -1) {
						while (m[last_second]->second) {
							if (m[last_second]->c == looking_for) {
								// found it, look for a forward match
								for (size_t j = i + 1; j < size && !m[j]->second; ++j) {
									if (m[j]->c == looking_for) {
										// found it!
										percolating = true;
										m[last_second]->second = false;
										m[j]->second = true;
										goto made_a_long_distance_swap;
									}
								}
							}
							--last_second;
						}
					}
				} else {
					++fir_i;
				}
			}
		}
		continue;

made_a_long_distance_swap:
		percolating = true; // and then actually continue!
	}
}

/* check if whatever we ended up with after percolating actually constitutes a
   valid solution */
bool verify_post(const string& m, const string& fir, const string& sec) {
	size_t m_i = 0;
	size_t fir_i = 0;
	size_t sec_i = 0;

	for (; m_i < m.size(); ++m_i) {
		if (isupper(m[m_i])) { // came from first
			// if we ran out of characters or don't match, return!
			if (fir_i == fir.size() || fir[fir_i] != tolower(m[m_i])) {
				return false;
			}
			++fir_i;
		} else {
			if (sec_i == sec.size() || sec[sec_i] != m[m_i]) {
				return false;
			}
			++sec_i;
		}
	}

	// finally, see if we made it to the end
	return m_i == m.size() && fir_i == fir.size() && sec_i == sec.size();
}

pair<bool, string> is_merge_of(const string& merge,
                               const string& first,
                               const string& second) {
	// try to set up our data structure
	auto m = create_extra_string(merge);
	if (!mark_seconds(m, second)) goto not_a_merge;

	// percolate characters towards the end
	percolate(m, first, second);
	print_it(m);

	// reconstruct the string
reconstruct: { // for scoping
		string post_merge(merge.length(), '\0');
		for (auto& e : m) {
			post_merge[e.orig_pos] = e.second ? e.c : toupper(e.c);
		}

		if (!verify_post(post_merge, first, second)) goto not_a_merge;
		return pair<bool, string>(true, post_merge);
	}

not_a_merge:
	return pair<bool, string>(false, "");
}

int main() {
	auto res = is_merge_of("cchocholaiptes", "chocolate", "chips");
	cout << "merge: " << (res.first ? "yes" : "no") << '\n';
	res = is_merge_of("ababacd", "abac", "bad");
	cout << "merge: " << (res.first ? "yes" : "no") << '\n';
	res = is_merge_of("abab", "ab", "ba");
	cout << "merge: " << (res.first ? "yes" : "no") << '\n';
	return 0;

	string input;
	read: { // for scoping
		ifstream in_file(prompt("Enter name of input file: "));
		read_file(in_file, input);
	}

	istringstream in_stream(input);
	ostringstream output;
	string first;
	string second;
	string merge;
	while (!getline(in_stream, first).eof()) {
		getline(in_stream, second);
		getline(in_stream, merge);

		auto result = is_merge_of(merge, first, second);
		if (result.first) output << result.second << '\n';
		else output << "*** NOT A MERGE ***\n";
	}

	write: {
		ofstream out_file(prompt("Enter name of output file: "));
		out_file << output.str();
	}

	return 0;
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
