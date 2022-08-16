#pragma once


class DirectedEdge
{
private:

	int m_SrcVertex;
	int m_DstVertex;
	int m_EdgeCapacity;
	int m_CurrFlow;

public:

	void SetSrcVertex(int i_SrcVertex) { m_SrcVertex = i_SrcVertex; }
	void SetDstVertex(int i_DstVertex) { m_DstVertex = i_DstVertex; }
	void SetEdgeCapacity(int i_EdgeCapacity) { m_EdgeCapacity = i_EdgeCapacity; }
	void SetCurrFlow(int i_CurrFlow) { m_CurrFlow = i_CurrFlow; }
	
};
