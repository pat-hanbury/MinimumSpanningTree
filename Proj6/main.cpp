//John Kang and Patrick Hanbury
//Project 6a
//Algorithms

//bool function that returns true if all nodes are visited. 
bool allNodesVisited(Graph &g) {
	//verteices and graph descriptors
	std::pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	//for loop to iterate over each loop
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
		//if statement that says if a node was not visisted, then return false
		if (!g[*vItr].visited)
			return false;
	}
	//else true
	return true;
}

//bool function that returns true if graph is connected.
bool isConnected(Graph &g) {
	//resets the visit property 
	clearVisited(g);/
	//store iterators for the list of nodes in the graph. 
	std::pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	//iterates from start node to the end node
	dfs(g, *vItrRange.first);
	//runs funciton to check all nodes
	if (allNodesVisited(g))
		return true;
	else
		return false;
}


//bool function that returns true if graph is cyclic
bool isCyclic(Graph &g) { 
	//resets visit property
	clearVisited(g);
	//vertex decsriptprs
	//stack 'search' for traverses
	std::pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> currentMoves;
	std::stack<Graph::vertex_descriptor> search;
	//stores current node in 'current'
	Graph::vertex_descriptor current;
	//for statement that iterate over all nodes in the graph
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
		//if current node is not visisted
		if (!g[*vItr].visited) {
			//push it in the stack
			search.push(*vItr);
			//while statment to search the stack if it is not empty
			while (!search.empty()) {
				//searchs the top of the stack
				current = search.top();
				//pops the top of the stack
				search.pop();
				//marks as true.
				g[current].visited = true;
				//sets moves ranged based on current vertices
				currentMoves = adjacent_vertices(current, g);
				
				//for statement that iterates through the nodes
				for (Graph::adjacency_iterator adjacent = currentMoves.first; adjacent != currentMoves.second; ++adjacent) {
					//if statement that checks the child nodes
					if (!g[*adjacent].visited) {
						//pushes node onto search stack
						search.push(*adjacent);
						//stores the parent node in pred 
						g[*adjacent].pred = current;
					}
					//if the node has been visited and is not the parent then return fa;se
					else if (*adjacent != g[current].pred)
						return false;
				}
			}
		}
	}
	//return true if no cycles are found
	return true;
}

//void function that contains a spanning forrest
void findSpanningForest(Graph &g, Graph &sf) { 
	//resets the graph properties
	clearVisited(g);
	clearMarked(g);
	//store the range of nodes in the graph
	std::pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	Graph::vertex_descriptor v;
	//for loop to iterate overthe entire graph
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
		//ads the nodes to the new graph 
		v = add_vertex(sf);
	}
	//runs the breadth first search that also adds edges to the new graph
	bfs(g, sf);
	return;
}


//MOdified BFS to add edges to a graph to create a spanning forest. Essentially, the visit property determines whether the children of the node was looked at. 
//The marked property determines whether the node has been added to the spanning tree. 
void bfs(Graph &g, Graph &sf) {
	//store the range of vertices of the input graph
	//variable to store iterators for adjcaent nodes to current node.
	//queue to facilitate BFS
	std::pair<Graph::vertex_iterator, Graph::vertex_iterator> startToEnd = vertices(g);
	std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> currentMoves;
	std::queue<Graph::vertex_descriptor> search;
	Graph::vertex_descriptor current;//store current node
	//for loop to iterate over every node of the graph
	for (Graph::vertex_iterator vItr = startToEnd.first; vItr != startToEnd.second; ++vItr) {
		//if statement to check if current node has not been visisted
		if (!g[*vItr].visited) {
			//pushes to search queue
			search.push(*vItr);
			//mark node as true, children nhave not necessiarly been checked.
			g[*vItr].marked = true; 
			//while statement to check if queue is not empty
			while (!search.empty()) {
				//sets current to front of queue
				current = search.front();
				//pops top element
				search.pop();
			//if statement to check if the node has been visisted
			if (!g[current].visited) {
					//marks children node as true
					g[current].visited = true;
					//stores the adjacenet nodes
					currentMoves = adjacent_vertices(current, g);
					//for loop that iterates over the adjacent nodes
					for (Graph::adjacency_iterator adjacent = currentMoves.first; adjacent != currentMoves.second; ++adjacent) {
						//if statment that checks if the current node ispart of tree or not
						if (!g[*adjacent].marked) {
							//pushes it to queue
							search.push(*adjacent);
							//repeat of above, marks, adjacent as current
							g[*adjacent].marked = true;
							//adds edge current and parents
							add_edge(*adjacent, current, sf);
							add_edge(current, *adjacent, sf);
						}
					}
				}
			}
		}
	}
}


//MOdified DFS that should check each through from top and bottom, increasing in detph. 
void dfs(Graph & g, Graph::vertex_descriptor v) {
	//iterates to store moves from current node
	//stack 'search' for traversing
	std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> currentMoves;
	std::stack<Graph::vertex_descriptor> search;
	Graph::vertex_descriptor current;//stores the current node being used
	//pushes the node in the stack
	search.push(v);
	//while the the stack is not empty
	while (!search.empty()) {
		//stores the top of the stack
		current = search.top();
		//pops the top of the stack
		search.pop();
		//if the current node was not visisted
		if (!g[current].visited) {
			//mark that node as true
			g[current].visited = true;
			//set the possible moves based on the current vertex
			currentMoves = adjacent_vertices(current, g);
			//for loop to iterate over the current possible moves
			for (Graph::adjacency_iterator adjacent = currentMoves.first; adjacent != currentMoves.second; ++adjacent) {
				//if the child node was viissted, push that onto the stack. 
				if (!g[*adjacent].visited) {
					search.push(*adjacent);
				}
			}
		}
	}
}






