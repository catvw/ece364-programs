/* Driver program for the spellchecker. */

//#include "spell/checker.h"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using system_clock = std::chrono::system_clock;
using time_type = std::chrono::duration<float>;

int main() {
	// set cout to fixed precision, 3 decimal places
	std::cout << std::fixed << std::setprecision(3);

	std::string dict_file;
	std::cout << "Enter name of dictionary: ";
	std::getline(std::cin, dict_file);

	system_clock::time_point start = system_clock::now();

	std::ifstream dict_in(dict_file);
	std::string dict;

	system_clock::time_point end = system_clock::now();

	time_type dict_loading_time =
		std::chrono::duration_cast<time_type>(end - start);
	std::cout << dict_loading_time.count();

	// get until EOF, so long as we don't see any null characters
	std::getline(dict_in, dict, '\0');

	std::cout << dict;
/*
	std::string input_file;
	std::cout << "Enter name of input file: ";
	std::getline(std::cin, input_file);

	std::string output_file;
	std::cout << "Enter name of output file: ";
	std::getline(std::cin, output_file);
*/
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
