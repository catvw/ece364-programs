#include <cctype>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

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

pair<bool, string> is_merge_of(const string& merge,
                               const string& string1,
                               const string& string2) {
	auto m = merge.begin();
	auto s1 = string1.begin();
	auto s2 = string2.begin();
	size_t block_length = 0;

	string ret(merge.length(), '\0');
	auto r = ret.begin();

	bool reverse = false;
	while (true) {
		//cout << *s1 << ' ' << *s2 << ' ' << ret << "\n";
		const bool end_of_m = (m == merge.end());
		const bool end_of_s1 = (s1 == string1.end());
		const bool end_of_s2 = (s2 == string2.end());

		if (end_of_m && end_of_s1 && end_of_s2) {
			// made it to the end!
			return pair<bool, string>(true, ret);
		}

		auto s2_ahead = s2 + block_length;

		// if we can consume a character from s1, do so
		if (!reverse && !end_of_s1 && *s1 == *m) {
			if (s2_ahead < string2.end() && *s1 == *s2_ahead) {
				// inside an identical block, so increment
				++block_length;
			} else block_length = 0;

			*r = toupper(*m);
			++m;
			++r;
			++s1;
		} else if (!end_of_s2 && *s2 == *m) { // try the other string
			*r = tolower(*m);
			++m;
			++r;
			++s2;
			block_length = 0; // definitely not identical!
			reverse = false;
		} else {
			// go back to the start of the last block
			m -= block_length;
			r -= block_length;
			s1 -= block_length;

			// see if we can use the other block
			if (s2_ahead < string2.end()
					&& *s2_ahead == *(m + block_length)) {
				for (; block_length > 0; --block_length) {
					*r = tolower(*m);
					++m;
					++r;
					++s2;
				}
			} else { // go back to the last fork before this one
				if (s1 == string1.begin()) { // can't back up further!
					return pair<bool, string>(false, "");
				}

				while (*(m - 1) == *(r - 1)) { // while lowercase
					--m;
					--r;
					--s2;
				}

				--m;
				--r;
				--s1; // one more step back
				reverse = true;
			}
		}
	}
}

int main() {
	string input;
	read: { // for scoping
		ifstream in_file(prompt("Enter name of input file: "));
		read_file(in_file, input);
	}

	istringstream in_stream(input);
	ostringstream output;
	string string1;
	string string2;
	string merge;
	while (!getline(in_stream, string1).eof()) {
		getline(in_stream, string2);
		getline(in_stream, merge);

		auto result = is_merge_of(merge, string1, string2);
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
