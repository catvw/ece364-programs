/* Driver program to test Dijkstra's algorithm. */

#include "dijkstra/graph.h"
//#include <algorithm>
//#include <cctype>
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

int main(int argc, char** argv) {
	// set cout to fixed precision, 6 decimal places
	std::cout << std::fixed << std::setprecision(6);

	// see whether we can skip the prompts
	bool do_prompt = argc != 4;

	std::string graph_str;
	if (do_prompt) {
		std::ifstream graph_file(prompt("Enter name of graph file: "));
		read_file(graph_file, graph_str);
	} else {
		std::ifstream graph_file(argv[1]);
		read_file(graph_file, graph_str);
	}
	graph g(graph_str);

	std::string start_vertex;
	if (do_prompt) {
		// prompt until they give us a valid starting vertex
		do {
			start_vertex = prompt("Enter name of starting vertex: ");
		} while (!g.has_vertex(start_vertex));
	} else {
		start_vertex = argv[2];
		if (!g.has_vertex(start_vertex)) return 1;
	}

	// apply Dijkstra's algorithm
	pathtree p;
	time_and_report([&]() {
		p = find_best_paths(g, start_vertex);
	}, "Total time (in seconds) to apply Dijkstra's algorithm: ");

	std::string out_file;
	if (do_prompt) {
		out_file = prompt("Enter name of output file: ");
	} else {
		out_file = argv[3];
	}

	std::ofstream out(out_file);
	out << p;
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
