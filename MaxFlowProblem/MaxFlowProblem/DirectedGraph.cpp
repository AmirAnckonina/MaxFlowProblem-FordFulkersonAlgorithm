#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(int i_NumOfVertices, int i_NumOfEdges)
{
	m_NumOfVertices = i_NumOfVertices;
	m_NumOfEdges = i_NumOfEdges;
}

DirectedGraph::DirectedGraph(const DirectedGraph& i_GraphToCopy)
{
	int tmpSrcVertex, tmpDstVertex, tmpEdgeCapacity;
	int numOfNbrs;

	MakeEmptyGraph(i_GraphToCopy.m_NumOfVertices);
	m_NumOfEdges = i_GraphToCopy.m_NumOfEdges;

	/// Copy ***by value*** the map representing the nbr's of each vertex.
	/// AddEdge allocating a new "DirectedEdge" obj.
	for (int vertex = 1; vertex <= i_GraphToCopy.m_AdjacencyList.size(); vertex++)
	{
		list<DirectedEdge>::iterator vertexNbrsItr;
		list<DirectedEdge> currNbrsList = i_GraphToCopy.m_AdjacencyList[vertex - 1];
		for (vertexNbrsItr = currNbrsList.begin(); vertexNbrsItr != currNbrsList.end(); vertexNbrsItr++)
		{
			tmpSrcVertex = vertexNbrsItr->m_SrcVertex;
			tmpDstVertex = vertexNbrsItr->m_DstVertex;
			tmpEdgeCapacity = vertexNbrsItr->m_EdgeCapacity;
			AddEdge(tmpSrcVertex, tmpDstVertex, tmpEdgeCapacity);
		}
	}
}

DirectedGraph::~DirectedGraph()
{
	/// Release all edges allocations.
}

void DirectedGraph::MakeEmptyGraph(int i_NumOfVertices)
{
	m_NumOfVertices = i_NumOfVertices;

	for (int idx = 0; idx < i_NumOfVertices; idx++)
	{
		list<DirectedEdge> newNeighborsListOfSingleVertex;
		m_AdjacencyList.push_back(newNeighborsListOfSingleVertex);
	}
}

void DirectedGraph::AddEdge(int i_SrcVertex, int i_DstVertex, int i_EdgeCapacity)
{
	DirectedEdge newEdge(i_SrcVertex, i_DstVertex, i_EdgeCapacity);
	m_AdjacencyList[i_SrcVertex - 1].push_back(newEdge);
}

/// TEST!!!!
void DirectedGraph::RemoveEdge(int i_SrcVertex, int i_DstVertex)
{
	list<DirectedEdge> nbrsList = m_AdjacencyList[i_SrcVertex - 1];
	list<DirectedEdge>::iterator nbrsItr;
	
	for (nbrsItr = nbrsList.begin(); nbrsItr != nbrsList.end(); nbrsItr++)
	{
		if (nbrsItr->m_DstVertex == i_DstVertex)
		{
			nbrsList.erase(nbrsItr);
			break;
		}
	}
}

DirectedEdge& DirectedGraph::GetEdge(int i_SrcVertex, int i_DstVertex)
{
	/// Check if the returned edge is a value or reference.
	list<DirectedEdge> nbrsList = m_AdjacencyList[i_SrcVertex - 1];
	list<DirectedEdge>::iterator nbrsItr;
	DirectedEdge edge;

	for (nbrsItr = nbrsList.begin(); nbrsItr != nbrsList.end(); nbrsItr++)
	{
		if (nbrsItr->m_DstVertex == i_DstVertex)
		{
			edge = *nbrsItr;
			break;
		}
	}

	return edge;
}

/// TEST!!!!
list<DirectedEdge>& DirectedGraph::GetVertexAdjList(int i_Vertex)
{
	return m_AdjacencyList[i_Vertex - 1];
}
