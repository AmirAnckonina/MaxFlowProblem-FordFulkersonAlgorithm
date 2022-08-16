#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(int i_NumOfVertices, int i_NumOfEdges)
{
	m_NumOfVertices = i_NumOfVertices;
	m_NumOfEdges = i_NumOfEdges;
}

DirectedGraph::~DirectedGraph()
{
	/// Release all edges allocations.
}

void DirectedGraph::MakeEmptyGraph(int i_NumOfVertices)
{

}
