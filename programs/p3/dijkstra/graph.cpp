#include "graph.h"

#include <sstream>
#include <utility>

using namespace std;

graph::graph(const string& g) {
	istringstream in(g);

	bool not_eof = true;
	while (not_eof) {
		string from;
		string to;
		unsigned int cost;

		not_eof = !(in >> from).eof();
		if (not_eof) { // we got something!
			in >> to >> cost;
			add_edge(from, to, cost);
		}
	}
}

void graph::add_edge(const string& from,
                     const string& to,
                     unsigned int cost) {
	add_vertex(from);
	add_vertex(to);

	vertex* from_v = static_cast<vertex*>(adj_list.getPointer(from));
	from_v->add_edge(to, cost);
}

void graph::add_vertex(const string& n) {
	if (!has_vertex(n)) {
		// hey, *you* made me do this, not me
		adj_list.insert(n, new vertex(n));
	}
}

bool graph::has_vertex(const string& n) const {
	return adj_list.contains(n);
}

graph::vertex::vertex(const string& name) : name{name} { }

void graph::vertex::add_edge(const string& to, unsigned int cost) {
	// note: should probably check if this edge already exists, but...
	edges.push_back(move(edge{to, cost}));
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
