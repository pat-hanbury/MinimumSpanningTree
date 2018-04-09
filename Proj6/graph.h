#include <fstream>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

struct VertexProperties; //data structure containing properties for each node
struct EdgeProperties; //data structure containing properties for each edge

//customize adjacency list with a vector for nodes and a vector for edges, as well as custom properties
typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

#define LargeValue 99999999
#define noPred 99999999

struct VertexProperties
{
	pair<int,int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred; // predecessor node
	int weight;
	bool visited;
	bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};

//overloaded print operator for custom graph type
inline std::ostream & operator << (std::ostream & ostr, const Graph & g) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); //hold iterators for beginning and end of node vector
	pair <Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g); //hold iterators for beginning and end of edge vector
	//iterate over entire node vector
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) {
		//print the properties of the nodes
		ostr << "	node: " << *vItr << std::endl;
		ostr << "	cell: " << g[*vItr].cell.first << "," << g[*vItr].cell.second << std::endl;
		ostr << "	weight: " << g[*vItr].weight << std::endl;
		ostr << "	visited: " << g[*vItr].visited << std::endl;
		ostr << "	marked: " << g[*vItr].marked << std::endl;
	}
	//iterate over edge vector, print out edge descriptor
	for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; eItr++) {
		ostr << "	edge: " << source(*eItr, g) << "," << target(*eItr, g) << std::endl;
	}
	return ostr;
}

void clearVisited(Graph &g) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		g[*vItr].visited = false;
}
// Mark all nodes in g as not visited.

void clearMarked(Graph &g) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		g[*vItr].marked = false;
}

#endif
