/* Driver program for the spellchecker. */

#include "spell/checker.h"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using system_clock = std::chrono::system_clock;
using time_type = std::chrono::duration<float>;

std::string prompt(const char* pr) {
	std::string dict_file;
	std::cout << pr;
	std::getline(std::cin, dict_file);
	return dict_file;
}

std::string read_file(std::istream& file, std::string& out) {
	// get until EOF, so long as we don't see any null characters
	std::getline(file, out, '\0');
	std::transform(out.begin(), out.end(), out.begin(), tolower);
	return out;
}

template<typename Task>
void time_and_report(Task t, const std::string& message) {
	system_clock::time_point start = system_clock::now();
	t();
	system_clock::time_point end = system_clock::now();

	time_type elapsed = std::chrono::duration_cast<time_type>(end - start);
	std::cout << message << elapsed.count() << '\n';
}

int main() {
	// set cout to fixed precision, 3 decimal places
	std::cout << std::fixed << std::setprecision(3);

	std::ifstream dict_file(prompt("Enter name of dictionary: "));
	checker ch;
	ch.set_max_word_length(20);

	// load the dictionary
	time_and_report([&]() {
		std::string dict;
		read_file(dict_file, dict);
		ch.add_words(dict);
	}, "Total time (in seconds) to load dictionary: ");

	std::ifstream in_file(prompt("Enter name of input file: "));
	std::ofstream out_file(prompt("Enter name of output file: "));

	time_and_report([&]() {
		std::string in;
		read_file(in_file, in);
		out_file << ch.check(in);
	}, "Total time (in seconds) to check document: ");
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
