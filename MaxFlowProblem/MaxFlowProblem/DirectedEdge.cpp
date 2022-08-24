#include "DirectedEdge.h"

DirectedEdge::DirectedEdge(int i_SrcVertex, int i_DstVertex, int i_EdgeCapacity, int i_CurrFlow)
{
	m_SrcVertex = i_SrcVertex;
	m_DstVertex = i_DstVertex;
	m_EdgeCapacity = i_EdgeCapacity;
	m_CurrFlow = i_CurrFlow;
}
