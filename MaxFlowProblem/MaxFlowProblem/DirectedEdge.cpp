#include "DirectedEdge.h"

DirectedEdge::DirectedEdge(int srcVertex, int dstVertex, int edgeCapacity, int currFlow)
{
	m_SrcVertex = srcVertex;
	m_DstVertex = dstVertex;
	m_EdgeCapacity = edgeCapacity;
	m_CurrFlow = currFlow;
}
