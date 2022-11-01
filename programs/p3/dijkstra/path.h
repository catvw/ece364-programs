/* Pathfinding utilities. Here be Dijkstra... */

#ifndef PATH_H
#define PATH_H

class pathtree;

#include "graph.h"
#include <ostream>

/* Represents a tree of paths to vertices, keyed by vertex. Done... mostly
   because I felt like it. */
class pathtree {
public:
	pathtree() = default;

private:
	struct path {
		std::vector<std::string> vertices;
		int distance;
	};

	std::vector<path> paths;

	friend std::ostream& operator<<(std::ostream&, const pathtree&);
	friend pathtree find_best_paths(const graph&, const std::string&);
};

/* Write a pathtree to standard output. */
std::ostream& operator<<(std::ostream&, const pathtree&);

/* Find the best paths from the given starting vertex to every other vertex. */
pathtree find_best_paths(const graph&, const std::string&);

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
