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
using namespace std;

class MaxFlowProgram
{

private:
	static constexpr int INFINITE = -1;

	struct FlowPath
	{
		list<int> verticesList;
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
	bool EdgeInputValidation(int i_SrcVertex, int i_DstVertex, int i_EdgeCapacity, int i_NumOfVertices);
	bool VertexInRange(int i_Vertex, int i_MaxVertexIdx);
	void FordFulkersonBFS();
	vector<int> BFS(DirectedGraph& i_Graph, int i_SrcVertex);
	void InitBFSVectors(vector<int>& d, vector<int>& p, int i_SrcVertex);
	void UpdateGraphs(DirectedGraph& i_OriginalGraph, DirectedGraph& i_ResidualGraph, FlowPath i_ReturnedPath);
	FlowPath ExtractFlowPath(DirectedGraph& i_ResidualGraph, vector<int> i_Parent, int i_StartingVertexG1, int i__EndingVertexG1);

};

