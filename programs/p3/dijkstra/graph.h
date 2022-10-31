/* Graph class. Represents a graph. Very graphic.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <string>

class graph {
public:
	/* Use the given string (assumed to be in Sable's special format) to
	   initialize the graph. */
	graph(std::string&);

	/* Check if the graph has a vertex by the given name. */
	bool has_vertex(std::string&);
private:
};

#endif
