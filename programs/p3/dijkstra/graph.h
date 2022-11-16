/* Graph class. Represents a graph. Very graphic.
 */

#ifndef GRAPH_H
#define GRAPH_H

class graph;

#include "hash/hash.h"
#include "path.h"
#include <string>
#include <vector>

class graph {
public:
	/* Use the given string (assumed to be in Sable's special format) to
	   initialize the graph. */
	graph(const std::string&);

	/* Add an edge to the graph, with a given cost. Vertices are not required
	   to exist prior to their use here. */
	void add_edge(const std::string& from, const std::string& to, int);

	/* Add an unconnected vertex to the graph. */
	void add_vertex(const std::string&);

	/* Check if the graph has a vertex by the given name. */
	bool has_vertex(const std::string&) const;

private:
	struct edge {
		std::string to; // string id, for now
		int cost;
	};

	struct vertex {
		vertex(const std::string&);

		/* Add an outbound edge with the given cost. */
		void add_edge(const std::string& to, int);

		std::string name;
		std::vector<edge> edges;

		// used for the pathfinding algorithm!
		mutable bool known;
		mutable int distance;
		mutable vertex* previous;
	};

	std::vector<std::string> vertices; // so that we can iterate over them
	mutable hashTable adj_list; // XXX: should be better qualified itself!

	// because I *never* get to use this, and there aren't enough friends
	friend pathtree find_best_paths(const graph&, const std::string&);
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
