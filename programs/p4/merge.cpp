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

	string ret(merge.length(), '\0');
	auto r = ret.begin();

	bool reverse = false;
	while (true) {
		const bool end_of_m = (m == merge.end());
		const bool end_of_s1 = (s1 == string1.end());
		const bool end_of_s2 = (s2 == string2.end());

		// if we can consume a character from s1, do so
		if (!reverse && !end_of_s1 && *s1 == *m) {
			*r = toupper(*m);
			++m;
			++r;
			++s1;
		} else if (!end_of_s2 && *s2 == *m) { // try the other string
			*r = tolower(*m);
			++m;
			++r;
			++s2;
			reverse = false; // no need to keep reversing
		} else if (end_of_m && end_of_s1 && end_of_s2) {
			// made it to the end!
			return pair<bool, string>(true, ret);
		} else { // try backing up
			if (s1 == string1.begin()) { // can't back up!
				return pair<bool, string>(false, "");
			} else {
				--m;
				--r;
				--s1;
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
