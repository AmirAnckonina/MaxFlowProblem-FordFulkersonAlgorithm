#pragma once
#include <iostream>
#include <list>
#include "DirectedEdge.h"
#include <map>
#include <vector>
using namespace std;

class DirectedGraph
{
private:
	int m_NumOfVertices;
	int m_NumOfEdges;
	vector<list<DirectedEdge>> m_AdjacencyList;
	///vector<list<DirectedEdge*>> m_AdjacencyList;


public:
	DirectedGraph(int i_NumOfVertices = 0, int i_NumOfEdges = 0);
	DirectedGraph(const DirectedGraph& i_GraphToCopy);
	~DirectedGraph();
	void MakeEmptyGraph(int i_NumOfVertices);
	void SetNumOfVertices(int i_NumOfVertices) { m_NumOfVertices = i_NumOfVertices; }
	int GetNumOfVertices() { return m_NumOfVertices; }
	void SetNumOfEdges(int i_NumOfEdges) { m_NumOfEdges = i_NumOfEdges; }
	int GetNumOfEdges() { return m_NumOfEdges; }
	void AddEdge(int i_SrcVertex, int i_DstVertex, int i_EdgeCapacity);
	void RemoveEdge(int i_SrcVertex, int i_DstVertex);
	DirectedEdge& GetEdge(int i_SrcVertex, int i_DstVertex);
	list<DirectedEdge>& GetVertexAdjList(int i_Vertex);
	vector<list<DirectedEdge>>& GetGraphAdjList() { return m_AdjacencyList; }

};

