#pragma once
#include <iostream>
#include <list>
#include "DirectedEdge.h"
#include <map>
#include <vector>
#include <queue>
#include "GraphCut.h"
using namespace std;

class MaxFlowProgram;

class DirectedGraph
{
private:
	int m_NumOfVertices;
	int m_NumOfEdges;
	vector<list<DirectedEdge*>> m_AdjacencyList;

public:
	DirectedGraph(int numOfVertices = 0, int numOfEdges = 0);
	DirectedGraph(const DirectedGraph& graphToCopy);
	~DirectedGraph();
	void MakeEmptyGraph(int numOfVertices);
	void SetNumOfVertices(int numOfVertices) { m_NumOfVertices = numOfVertices; }
	int GetNumOfVertices() { return m_NumOfVertices; }
	void SetNumOfEdges(int numOfEdges) { m_NumOfEdges = numOfEdges; }
	int GetNumOfEdges() { return m_NumOfEdges; }
	void AddEdge(int srcVertex, int dstVertex, int edgeCapacity);
	void RemoveEdge(int srcVertex, int dstVertex);
	DirectedEdge* GetEdge(int srcVertex, int dstVertex);
	list<DirectedEdge*>* GetVertexAdjList(int vertex);
	vector<list<DirectedEdge*>>* GetGraphAdjList() { return &m_AdjacencyList; }
	void BFS(int srcVertex, vector<int>& dist, vector<int>& parent);
	void InitVectors(vector<int>& dist, vector<int>& parent, int srcVertex);
	void Dijkstra(int srcVertex, vector<int>& dist, vector<int>& parent);
	GraphCut ExtractGraphCut(DirectedGraph& residualGraph, int srcVertex, int dstVertex, vector<int>& dist);
	void PrintGraph();
};

