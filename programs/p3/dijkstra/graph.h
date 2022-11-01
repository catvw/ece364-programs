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
	void add_edge(const std::string& from,
	              const std::string& to,
	              unsigned int);

	/* Add an unconnected vertex to the graph. */
	void add_vertex(const std::string&);

	/* Check if the graph has a vertex by the given name. */
	bool has_vertex(const std::string&) const;

private:
	struct edge {
		std::string to; // string id, for now
		unsigned int cost;
	};

	struct vertex {
		vertex(const std::string&);

		/* Add an outbound edge with the given cost. */
		void add_edge(const std::string& to, unsigned int);

		std::string name;
		std::vector<edge> edges;

		// used for pathfinding algorithm!
		mutable unsigned int distance;
		mutable vertex* previous;

	};

	mutable hashTable adj_list; // XXX: should be better qualified itself!

	// because I *never* get to use this, and there aren't enough friends
	friend pathtree find_best_paths(const graph&, const std::string&);
};

#endif
