#include "path.h"

#include "heap/heap.h"
#include <limits>

using namespace std;

// because no path will EVER be longer than this... right?
constexpr const int nearly_infinite = std::numeric_limits<int>::max();

pathtree find_best_paths(const graph& g, const string& v) {
	using edge = graph::edge;
	using vertex = graph::vertex;
	using path = pathtree::path;

	/* initialize everything for Dijkstra's algorithm; heap keys represent
	   distances to each vertex */
	heap h(g.vertices.size());
	for (auto& name : g.vertices) {
		vertex* vert = static_cast<vertex*>(g.adj_list.getPointer(name));
		vert->distance = nearly_infinite;
		vert->known = false;
		vert->previous = nullptr;
		h.insert(vert->name, nearly_infinite, vert);
	}

	// set the root vertex to distance zero
	vertex* root = static_cast<vertex*>(g.adj_list.getPointer(v));
	root->distance = 0;
	h.setKey(v, 0);

	std::string id;
	int dist;
	vertex* vert;
	while(h.deleteMin(&id, &dist, &vert) != heap::heap_empty) {
		vert->known = true;

		for (auto& e : vert->edges) {
			vertex* next = static_cast<vertex*>(g.adj_list.getPointer(e.to));
			int new_dist = dist + e.cost;
			
			// not in the known set and should be updated
			if (!next->known && new_dist < next->distance) {
				next->distance = new_dist;
				h.setKey(next->name, new_dist);
				next->previous = vert; // lol
			}
		}
	}

	// build the pathtree
	pathtree tree;
	for (auto& name : g.vertices) {
		vert = static_cast<vertex*>(g.adj_list.getPointer(name));

		// walk backwards to the root vertex
		path p;
		p.to = vert->name;
		p.distance = vert->distance;
		vertex* prev = vert;
		while (prev) {
			p.vertices.push_back(prev->name);

			if (prev->previous == nullptr && prev != root) {
				// no way to continue, but we're not at the root, so no path
				p.vertices.resize(0);
			}
			prev = prev->previous;
		}

		tree.paths.push_back(p);
	}

	return tree;
}

ostream& operator<<(ostream& os, const pathtree& tree) {
	for (auto& path : tree.paths) {
		auto size = path.vertices.size();
		
		// write out the path tree
		os << path.to << ": ";
		if (size == 0) os << "NO PATH\n";
		else { // there is a path, so print it
			os << path.distance << " [";

			// since the paths are reversed, walk from the end to the start
			for (auto i = size - 1; i > 0; --i) {
				os << path.vertices[i] << ", ";
			}
			os << path.vertices[0] << "]\n";
		}
	}

	return os;
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
