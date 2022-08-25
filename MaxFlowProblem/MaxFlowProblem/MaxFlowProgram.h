#pragma once
#include <iostream>
#include <iterator>
#include <list>
#include<string>
#include <sstream>
#include<stdio.h>
#include <queue>
#include "DirectedGraph.h"
#include "DirectedEdge.h"
#include "GraphCut.h"
using namespace std;

class MaxFlowProgram
{

private:
	enum class Method {BFS, Dijkstra};
	static constexpr int INFINITE = -1;

	struct FlowPath
	{
		list<DirectedEdge*> pathEdgesList;
		int flowAmount = 0;
	};

	DirectedGraph m_GraphG1;
	int m_StartingVertexG1;
	int m_EndingVertexG1;
	DirectedGraph m_GraphG2;
	int m_StartingVertexG2;
	int m_EndingVertexG2;

public:
	void Run();
	void BuildDirectedGraphByInput();
	bool EdgeInputValidation(int srcVertex, int dstVertex, int edgeCapacity, int numOfVertices);
	bool VertexInRange(int vertex, int maxVertex);
	GraphCut FordFulkersonBFS();
	GraphCut FordFulkersonDijkstra();
	void UpdateGraphs(DirectedGraph& originalGraph, DirectedGraph& residualGraph, FlowPath& returnedPath);
	void SingleStepOriginalGraphUpdate(DirectedGraph& originalGraph, int flowAmount, int srcVertex, int dstVertex);
	void SingleStepResdiualGraphUpdate(DirectedGraph& residualGraph, int flowAmount, int srcVertex, int dstVertex);
	FlowPath ExtractFlowPath(DirectedGraph& residualGraph, vector<int>& parent, int startingVertexG1, int endingVertexG1);
	void PrintMinCutResult(GraphCut& minCut, Method method);
	void PostImprovingPathProcedure(DirectedGraph& originalGraph, DirectedGraph& residualGraph, vector<int>& D, vector<int>& P, int startingVertex, int endingVertex);
};

