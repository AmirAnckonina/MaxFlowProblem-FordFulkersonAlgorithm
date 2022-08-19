#pragma once
#include <iostream>
#include<list>
#include"verticesNodes.h"
#include<vector>

class Graph {
	std::vector<int> parent;
	std::list<vertices> edges;
	std::vector<int>distance;
	std::vector<std::vector<std::list<int>>> vertices;
	Graph(int verticess, int edges, int starting_edge, int ending_endge, std::list<vertices> full_edges);
};
