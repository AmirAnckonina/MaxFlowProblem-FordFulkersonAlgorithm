#include "MaxFlowProgram.h"

void MaxFlowProgram::Run()
{
    GraphCut minCutBFS, minCutDijkstra;
    BuildDirectedGraphByInput();
    m_GraphG1.PrintGraph();
    m_GraphG2.PrintGraph();
    minCutBFS = FordFulkersonBFS();
    PrintMinCutResult(minCutBFS, Method::BFS);
    minCutDijkstra = FordFulkersonDijkstra();
    PrintMinCutResult(minCutDijkstra, Method::Dijkstra);
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

bool MaxFlowProgram::EdgeInputValidation(int srcVertex, int dstVertex, int edgeCapacity, int numOfVertices)
{
    bool edgeInputIsValid;

    if (VertexInRange(srcVertex, numOfVertices) && VertexInRange(dstVertex, numOfVertices) && edgeCapacity >= 0) 
    {
        edgeInputIsValid = true;
    }

    else 
    {
        edgeInputIsValid = false;
    }

    return edgeInputIsValid;
}

bool MaxFlowProgram::VertexInRange(int vertex, int maxVertexIdx)
{
    bool inRange;

    if (vertex >= 0 && vertex <= maxVertexIdx)
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

GraphCut MaxFlowProgram::FordFulkersonBFS()
{
    GraphCut graphMinCut;
    DirectedGraph residualGraph = m_GraphG1;
    vector<int> D;
    vector<int> P;

    residualGraph.BFS(m_StartingVertexG1, D, P);

    while(D[m_EndingVertexG1 - 1] != INFINITE)
    {
        PostImprovingPathProcedure(m_GraphG1, residualGraph, D, P, m_StartingVertexG1, m_EndingVertexG1);
        residualGraph.BFS(m_StartingVertexG1, D, P);
    }

    /// Split the vertices to S and T grps and Calculate the maxFlow recieved at the end of the algorithm
    graphMinCut = m_GraphG1.ExtractGraphCut(residualGraph, m_StartingVertexG1, m_EndingVertexG1, D);

    return graphMinCut;
}

GraphCut MaxFlowProgram::FordFulkersonDijkstra()
{
    GraphCut graphMinCut;
    DirectedGraph residualGraph = m_GraphG2;
    vector<int> D;
    vector<int> P;

    /// Dijkstra...

    while (D[m_EndingVertexG1 - 1] != INFINITE)
    {
        PostImprovingPathProcedure(m_GraphG2, residualGraph, D, P, m_StartingVertexG2, m_EndingVertexG2);
        /// Dijkstra...
    }

    /// Split the vertices to S and T grps and Calculate the maxFlow recieved at the end of the algorithm
    graphMinCut = m_GraphG1.ExtractGraphCut(residualGraph, m_StartingVertexG1, m_EndingVertexG1, D);

    return graphMinCut;
}

void MaxFlowProgram::UpdateGraphs(DirectedGraph& originalGraph, DirectedGraph& residualGraph, FlowPath& returnedPath)
{
    list<DirectedEdge*>::iterator edgesItr;
    int currSrcVertex, currDstVertex, flowAmount = returnedPath.flowAmount;
    DirectedEdge* antiParallelEdgeOriginalGraph;
    DirectedEdge* antiParallelEdgeResidualGraph;

    for (edgesItr = returnedPath.pathEdgesList.begin(); edgesItr != returnedPath.pathEdgesList.end(); edgesItr++)
    {
        currSrcVertex = (*edgesItr)->GetSrcVertex();
        currDstVertex = (*edgesItr)->GetDstVertex();
        /// Update procedure in the original graph, for a single step in the path.
        SingleStepOriginalGraphUpdate(originalGraph, flowAmount, currSrcVertex, currDstVertex);
        /// Update procedure in the residual graph, for a single step in the path.
        SingleStepResdiualGraphUpdate(residualGraph, flowAmount, currSrcVertex, currDstVertex);
    }
}

void MaxFlowProgram::SingleStepOriginalGraphUpdate(DirectedGraph& originalGraph, int flowAmount, int srcVertex, int dstVertex)
{
    DirectedEdge* antiParallelEdge; 

    ///Update the flow in the current edge (OrginialGraph)
    originalGraph.GetEdge(srcVertex, dstVertex)->AddFlow(flowAmount);

    /// if there is anti-parallel edge -> update the flow there.
    antiParallelEdge = originalGraph.GetEdge(dstVertex, srcVertex);
    if (antiParallelEdge != nullptr)
    {
        antiParallelEdge->AddFlow((-1) * (flowAmount));
    }
}

void MaxFlowProgram::SingleStepResdiualGraphUpdate(DirectedGraph& residualGraph, int flowAmount, int srcVertex, int dstVertex)
{
    DirectedEdge* antiParallelEdge;

    residualGraph.GetEdge(srcVertex, dstVertex)->AddCapcaity((-1) * (flowAmount));
    if (residualGraph.GetEdge(srcVertex, dstVertex)->GetCapacity() == 0)
    {
        residualGraph.RemoveEdge(srcVertex, dstVertex);
    }

    antiParallelEdge = residualGraph.GetEdge(dstVertex, srcVertex);
    if (antiParallelEdge == nullptr) /// If there isn't anti-Parallel edge -> Add it!
    {
        residualGraph.AddEdge(dstVertex, srcVertex, flowAmount);
    }

    else /// The anti-parallel edge already exist, so just need to update the residual capacity
    {
        antiParallelEdge->AddCapcaity(flowAmount);
    }
}

MaxFlowProgram::FlowPath MaxFlowProgram::ExtractFlowPath(DirectedGraph& residualGraph, vector<int>& parent, int startingVertexG1, int endingVertexG1)
{
    FlowPath resFlowPath;
    int minEdgeCapacity = NULL, currEdgeCapacity, currVertex = endingVertexG1;
    DirectedEdge* currEdge;

    while (currVertex != startingVertexG1)
    {
        currEdge = residualGraph.GetEdge(parent[currVertex - 1], currVertex);
        resFlowPath.pathEdgesList.push_front(currEdge);
        currEdgeCapacity = currEdge->GetCapacity();
        if (currEdgeCapacity < minEdgeCapacity || minEdgeCapacity == NULL)
        {
            minEdgeCapacity = currEdgeCapacity;
        }

        currVertex = parent[currVertex - 1];
    }

    resFlowPath.flowAmount = minEdgeCapacity;

    return resFlowPath;
}

void MaxFlowProgram::PrintMinCutResult(GraphCut& minCut, Method method)
{
    if (method == Method::BFS)
    {
        cout << "BFS Method: " << endl;
    }

    else // Dijkstra
    {
        cout << "Greedy Method: " << endl;
    }

    cout << "Min Cut: ";
    minCut.PrintCut();
}

void MaxFlowProgram::PostImprovingPathProcedure(DirectedGraph& originalGraph, DirectedGraph& residualGraph, vector<int>& D, vector<int>& P, int startingVertex, int endingVertex)
{
    FlowPath returnedPath;

    returnedPath = ExtractFlowPath(residualGraph, P, startingVertex, endingVertex);
    UpdateGraphs(m_GraphG1, residualGraph, returnedPath);
    D.clear();
    P.clear();
}




