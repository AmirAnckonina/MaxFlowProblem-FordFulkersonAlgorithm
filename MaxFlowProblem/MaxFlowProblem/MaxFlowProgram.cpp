#include "MaxFlowProgram.h"

void MaxFlowProgram::Run()
{
    BuildDirectedGraphByInput();
    FordFulkersonBFS();
    
}

void MaxFlowProgram::BuildDirectedGraphByInput()
{
    int numOfVertices, numOfEdges, startingVertex, endingVertex;
    int tmpSrcVertex, tmpDstVertex, tmpEdgeCapacity;
    string rawInputForEdge;
    istringstream iss;

    cout << "Please enter the number of vertices: \n";
    cin >> numOfVertices;
    cout << "Please enter the number of edges:\n";
    cin >> numOfEdges;
    cout << " Please choose the source vertex: \n";
    cin >> startingVertex;
    cout << " Please choose the destination vertex: \n";
    cin >> endingVertex;
    cin.ignore();

    if (VertexInRange(startingVertex, numOfVertices) && VertexInRange(endingVertex, numOfVertices))
    {
        m_StartingVertexG1 = m_StartingVertexG2 = startingVertex;
        m_EndingVertexG1 = m_EndingVertexG2 = endingVertex;
    }

    m_GraphG1.MakeEmptyGraph(numOfVertices);
    cout << " Please enter the edges of the graph: \n";

    for (int i = 0; i < numOfEdges; i++) 
    { 
        rawInputForEdge.clear();
        iss.clear();
        getline(cin, rawInputForEdge);
        iss.str(rawInputForEdge);
        iss >> tmpSrcVertex;
        iss >> tmpDstVertex;
        iss >> tmpEdgeCapacity;
        if (EdgeInputValidation(tmpSrcVertex, tmpDstVertex, tmpEdgeCapacity, numOfVertices))
        {
            m_GraphG1.AddEdge(tmpSrcVertex, tmpDstVertex, tmpEdgeCapacity);
        }
    }
    
    /// Using copy c'tor to avoid any depedency of pointers and allocations.
    /// G1 is for BFS, G2 is for Ford-Fulkerson.
    m_GraphG2 = m_GraphG1;
}

bool MaxFlowProgram::EdgeInputValidation(int i_SrcVertex, int i_DstVertex, int i_EdgeCapacity, int i_NumOfVertices)
{
    bool edgeInputIsValid;

    if (VertexInRange(i_SrcVertex, i_NumOfVertices) && VertexInRange(i_DstVertex, i_NumOfVertices) && i_EdgeCapacity >= 0) 
    {
        edgeInputIsValid = true;
    }

    else 
    {
        edgeInputIsValid = false;
    }

    return edgeInputIsValid;
}

bool MaxFlowProgram::VertexInRange(int i_Vertex, int i_MaxVertexIdx)
{
    bool inRange;

    if (i_Vertex >= 0 && i_Vertex <= i_MaxVertexIdx)
    {
        inRange = true;
    }

    else
    {
        inRange = false;
        cout << "Sorry, vertex isn't in range!";
        exit(1);
    }

    return inRange;
}

void MaxFlowProgram::FordFulkersonBFS()
{
    /// Run BFS on residual graph and then extract the path from 's' to 't'
    /// If there's no path -> we're done.
    /// after each BFS we should update the Graph and the residual graph. 
    
    DirectedGraph residualGraph = m_GraphG1;
    vector<int> parent;
    int maxFlowInGraph;
    FlowPath returnedPath;

    parent = BFS(residualGraph, m_StartingVertexG1);

    while(parent[m_EndingVertexG1 - 1] != INFINITE)
    {
        returnedPath = ExtractFlowPath(residualGraph, parent, m_StartingVertexG1, m_EndingVertexG1);
        

        parent = BFS(residualGraph, m_StartingVertexG1);
    }
}

vector<int> MaxFlowProgram::BFS(DirectedGraph& i_ResidualGraph, int i_SrcVertex)
{
    vector<int> D(i_ResidualGraph.GetNumOfVertices());
    vector<int> P(i_ResidualGraph.GetNumOfVertices());
    queue<int> Q;
    list<DirectedEdge> NbrsListOfCurrVertex;
    list<DirectedEdge>::iterator nbrsItr;

    /// INIT:
    InitBFSVectors(D, P, i_SrcVertex);

    /// EnQueue the starting vertex.
    Q.push(i_SrcVertex);

    while (!Q.empty())
    {
        /// Get Vertex fron the queue.
        int currVertex = Q.front();
        Q.pop();
        NbrsListOfCurrVertex = i_ResidualGraph.GetVertexAdjList(currVertex);

        /// foreach neighbor of the current vertex.
        for (nbrsItr = NbrsListOfCurrVertex.begin(); nbrsItr != NbrsListOfCurrVertex.end(); nbrsItr++)
        {
            int currNbr = nbrsItr->GetDstVertex();
            if (D[currNbr - 1] == INFINITE)
            {
                D[currNbr - 1] = D[currVertex - 1] + 1;
                P[currNbr - 1] = currVertex;
                Q.push(currNbr);
            }
        }
    }

    return P;
}

void MaxFlowProgram::InitBFSVectors(vector<int>& io_D, vector<int>& io_P, int i_SrcVertex)
{
    for (int idx = 0; idx < io_D.size(); idx++)
    {
        io_D[idx] = INFINITE;
        io_P[idx] = NULL;
    }

    io_D[i_SrcVertex - 1] = 0;
}

void MaxFlowProgram::UpdateGraphs(DirectedGraph& i_OriginalGraph, DirectedGraph& i_ResidualGraph, FlowPath i_ReturnedPath)
{
    /// Extract the minimal flow in the received path
   /* int currVertex = i_EndingVertex;

    while (i_Parent[currVertex - 1] !=)*/

}

MaxFlowProgram::FlowPath MaxFlowProgram::ExtractFlowPath(DirectedGraph& i_ResidualGraph, vector<int> i_Parent, int i_StartingVertexG1, int i_EndingVertexG1)
{
    FlowPath resFlowPath;
    int currEdgeCapacity;
    int currVertex = i_EndingVertexG1;
    int minEdgeCapacity = i_ResidualGraph.GetEdge(i_Parent[currVertex - 1], currVertex).GetEdgeCapacity();

    resFlowPath.verticesList.push_front(currVertex);
    while (currVertex != i_StartingVertexG1)
    {
        currEdgeCapacity = i_ResidualGraph.GetEdge(i_Parent[currVertex - 1], currVertex).GetEdgeCapacity();
        if (currEdgeCapacity < minEdgeCapacity)
        {
            minEdgeCapacity = currEdgeCapacity;
        }

        currVertex = i_Parent[currVertex - 1];
        resFlowPath.verticesList.push_front(currVertex);
    }

    resFlowPath.flowAmount = minEdgeCapacity;

    return resFlowPath;
}




