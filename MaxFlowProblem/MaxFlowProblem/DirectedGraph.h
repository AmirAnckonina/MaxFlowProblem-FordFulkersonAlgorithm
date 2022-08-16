#pragma once
#include <iostream>
#include <list>
#include "DirectedEdge.h"
using namespace std;

class DirectedGraph
{
private:
	int m_NumOfVertices;
	int m_NumOfEdges;
	DirectedEdge** AdjecancyList;

public:
	DirectedGraph(int i_NumOfVertices, int i_NumOfEdges);
	~DirectedGraph();
	void SetNumOfVertices(int i_NumOfVertices) { m_NumOfVertices = i_NumOfVertices; }
	int GetNumOfVertices() { return m_NumOfVertices; }
	void SetNumOfEdges(int i_NumOfEdges) { m_NumOfEdges = i_NumOfEdges; }
	int GetNumOfEdges() { return m_NumOfEdges; }

	void MakeEmptyGraph(int i_NumOfVertices);
	//list GetAdjList(int i_Vertex);



	
};

