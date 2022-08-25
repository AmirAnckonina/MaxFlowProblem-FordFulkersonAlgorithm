#include "DirectedGraph.h"
#include "MaxFlowProgram.h"

DirectedGraph::DirectedGraph(int numOfVertices, int numOfEdges)
{
	m_NumOfVertices = numOfVertices;
	m_NumOfEdges = numOfEdges;
}

DirectedGraph::DirectedGraph(const DirectedGraph& graphToCopy)
{
	int tmpSrcVertex, tmpDstVertex, tmpEdgeCapacity;
	int numOfNbrs;

	MakeEmptyGraph(graphToCopy.m_NumOfVertices);
	m_NumOfEdges = graphToCopy.m_NumOfEdges;

	/// Copy ***by value*** the map representing the nbr's of each vertex.
	/// AddEdge allocating a new "DirectedEdge" obj.
	for (int vertex = 1; vertex <= graphToCopy.m_AdjacencyList.size(); vertex++)
	{
		const list<DirectedEdge*>* currNbrsList = &(graphToCopy.m_AdjacencyList[vertex - 1]);
		list<DirectedEdge*>::const_iterator vertexNbrsItr = vertexNbrsItr;
		for (vertexNbrsItr = currNbrsList->begin(); vertexNbrsItr != currNbrsList->end(); vertexNbrsItr++)
		{
			tmpSrcVertex = (*vertexNbrsItr)->m_SrcVertex;
			tmpDstVertex = (*vertexNbrsItr)->m_DstVertex;
			tmpEdgeCapacity = (*vertexNbrsItr)->m_EdgeCapacity;
			AddEdge(tmpSrcVertex, tmpDstVertex, tmpEdgeCapacity);
		}
	}
}

DirectedGraph::~DirectedGraph()
{
	/// Release all edges allocations.
}

void DirectedGraph::MakeEmptyGraph(int numOfVertices)
{
	m_NumOfVertices = numOfVertices;

	for (int idx = 0; idx < numOfVertices; idx++)
	{
		list<DirectedEdge*> newNeighborsListOfSingleVertex;
		m_AdjacencyList.push_back(newNeighborsListOfSingleVertex);
	}
}

void DirectedGraph::AddEdge(int srcVertex, int dstVertex, int edgeCapacity)
{
	DirectedEdge* newEdge = new DirectedEdge(srcVertex, dstVertex, edgeCapacity);
	m_AdjacencyList[srcVertex - 1].push_back(newEdge);
}

/// TEST!!!!
void DirectedGraph::RemoveEdge(int srcVertex, int dstVertex)
{
	list<DirectedEdge*>* nbrsList = &m_AdjacencyList[srcVertex - 1];
	list<DirectedEdge*>::iterator nbrsItr;
	
	for (nbrsItr = nbrsList->begin(); nbrsItr != nbrsList->end(); nbrsItr++)
	{
		if ((*nbrsItr)->m_DstVertex == dstVertex)
		{
			///nbrsList.erase(nbrsItr);
			nbrsList->remove(*nbrsItr);
			break;
		}
	}
}

DirectedEdge* DirectedGraph::GetEdge(int srcVertex, int dstVertex)
{
	/// Check if the returned edge is a value or reference.
	list<DirectedEdge*>* nbrsList = &m_AdjacencyList[srcVertex - 1];
	list<DirectedEdge*>::iterator nbrsItr;
	DirectedEdge* edge = nullptr;

	for (nbrsItr = nbrsList->begin(); nbrsItr != nbrsList->end(); nbrsItr++)
	{
		if ((*nbrsItr)->m_DstVertex == dstVertex)
		{
			edge = *nbrsItr;
			break;
		}
	}

	return edge;
}

/// TEST!!!!
list<DirectedEdge*>* DirectedGraph::GetVertexAdjList(int vertex)
{
	return &m_AdjacencyList[vertex - 1];
}


void DirectedGraph::BFS(int srcVertex, vector<int>& D, vector<int>& P)
{
	queue<int> Q;
	list<DirectedEdge*>* NbrsListOfCurrVertex;
	list<DirectedEdge*>::iterator nbrsItr;

	/// INIT:
	InitBFSVectors(D, P, srcVertex);

	/// EnQueue the starting vertex.
	Q.push(srcVertex);

	while (!Q.empty())
	{
		/// Get Vertex fron the queue.
		int currVertex = Q.front();
		Q.pop();
		NbrsListOfCurrVertex = GetVertexAdjList(currVertex);

		/// foreach neighbor of the current vertex.
		for (nbrsItr = NbrsListOfCurrVertex->begin(); nbrsItr != NbrsListOfCurrVertex->end(); nbrsItr++)
		{
			int currNbr = (*nbrsItr)->GetDstVertex();
			if (D[currNbr - 1] == INFINITE)
			{
				D[currNbr - 1] = D[currVertex - 1] + 1;
				P[currNbr - 1] = currVertex;
				Q.push(currNbr);
			}
		}
	}
}

void DirectedGraph::InitBFSVectors(vector<int>& D, vector<int>& P, int srcVertex)
{
	D.resize(m_NumOfVertices);
	P.resize(m_NumOfVertices);
	for (int idx = 0; idx < m_NumOfVertices; idx++)
	{
		D[idx] = INFINITE;
		P[idx] = NULL;
	}

	D[srcVertex - 1] = 0;
}

GraphCut DirectedGraph::ExtractGraphCut(DirectedGraph& residualGraph, int srcVertex, int dstVertex, vector<int>& D)
{
	GraphCut gCut;
	list<DirectedEdge*> SrcVertexNbrsList;
	list<DirectedEdge*>::iterator nbrsItr;

	for (int vertex = 1; vertex <= residualGraph.GetNumOfVertices(); vertex++)
	{
		if (D[vertex - 1] != INFINITE)
		{
			gCut.Sgrp.push_back(vertex);
		}

		else
		{
			gCut.Tgrp.push_back(vertex);
		}
	}

	gCut.cutFlow = 0;
	for (nbrsItr = SrcVertexNbrsList.begin(); nbrsItr != SrcVertexNbrsList.end(); nbrsItr++)
	{
		gCut.cutFlow += (*nbrsItr)->GetCurrFlow();
	}

	return gCut;
}


void DirectedGraph::PrintGraph()
{
	list<DirectedEdge*>::iterator edgesItr;

	for (int vertex = 1; vertex <= m_NumOfVertices; vertex++)
	{
		cout << "Vertex No. " << vertex << ": " << endl;
		list<DirectedEdge*>* currVertexList = GetVertexAdjList(vertex);
		for (edgesItr = currVertexList->begin(); edgesItr != currVertexList->end(); edgesItr++)
		{
			cout << "(" << (*edgesItr)->GetSrcVertex() << "," << (*edgesItr)->GetDstVertex() << ") F = " << (*edgesItr)->GetCurrFlow() << " , C = " << (*edgesItr)->GetCapacity() << endl;
		}
	}
}
