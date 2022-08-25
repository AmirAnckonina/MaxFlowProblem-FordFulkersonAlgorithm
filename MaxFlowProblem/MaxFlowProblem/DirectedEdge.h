#pragma once


class DirectedEdge
{
private:
	int m_SrcVertex;
	int m_DstVertex;
	int m_EdgeCapacity;
	int m_CurrFlow;
	friend class DirectedGraph;

public:
	DirectedEdge() { m_SrcVertex = m_DstVertex = m_EdgeCapacity = m_CurrFlow = 0; }
	DirectedEdge(int srcVertex, int dstVertex, int edgeCapacity, int currFlow = 0);
	void SetSrcVertex(int srcVertex) { m_SrcVertex = srcVertex; }
	void SetDstVertex(int dstVertex) { m_DstVertex = dstVertex; }
	void SetCapacity(int edgeCapacity) { m_EdgeCapacity = edgeCapacity; }
	void AddCapcaity(int capacityAmount) { m_EdgeCapacity += capacityAmount; }
	void AddFlow(int currFlow) { m_CurrFlow += currFlow; }
	int GetSrcVertex() { return m_SrcVertex; }
	int GetDstVertex() { return m_DstVertex; }
	int GetCapacity() { return m_EdgeCapacity; }
	int GetCurrFlow() { return m_CurrFlow; }
};

