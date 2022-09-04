#include "MaxFlowProgram.h"

void MaxFlowProgram::Run()
{
    /// Returning two minCuts for each implemention.
    GraphCut minCutBFS, minCutDijkstra;
    BuildDirectedGraphByInput();
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

    /// cout << "Please enter the number of vertices: \n";
    cin >> numOfVertices;
    /// cout << "Please enter the number of edges:\n";
    cin >> numOfEdges;
    /// cout << " Please choose the source vertex: \n";
    cin >> startingVertex;
    /// cout << " Please choose the destination vertex: \n";
    cin >> endingVertex;
    cin.ignore();

    if (BasicInputValidation(numOfVertices, numOfEdges, startingVertex, endingVertex))
    {
        m_GraphG1.MakeEmptyGraph(numOfVertices);
        m_StartingVertexG1 = m_StartingVertexG2 = startingVertex;
        m_EndingVertexG1 = m_EndingVertexG2 = endingVertex;
    }
        
    /// cout << " Please enter the edges of the graph: \n";

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

    /// Using operator to avoid any depedency of pointers and allocations.
    /// Therefore, copy the graph by value.
    /// G1 is for BFS, G2 is for Ford-Fulkerson.
    m_GraphG2 = m_GraphG1;
}

bool MaxFlowProgram::BasicInputValidation(int numOfVertices, int numOfEdges, int startingVertex, int endingVertex)
{
    bool inputIsValid;

    if (NumOfVerticesAndEdgesValidation(numOfVertices, numOfEdges) && 
        VertexInRange(startingVertex, numOfVertices) && 
        VertexInRange(endingVertex, numOfVertices))
    {
        inputIsValid = true;
    }

    else
    {
        inputIsValid = false;
        cout << "invalid input";
        exit(1);
    }

    return inputIsValid;
}

bool MaxFlowProgram::NumOfVerticesAndEdgesValidation(int numOfVertices, int numOfEdges)
{
    bool isValid;

    if (numOfVertices >= 0 && numOfEdges >= 0 && numOfEdges <= ((numOfVertices * (numOfVertices - 1)) / 2))
    {
        isValid = true;
    }

    else
    {
        isValid = false;
        cout << "invalid input";
        exit(1);
    }
    return isValid;
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
        cout << "invalid input";
        exit(1);

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
        cout << "invalid input";
        exit(1);
    }

    return inRange;
}

GraphCut MaxFlowProgram::FordFulkersonBFS()
{
    GraphCut graphMinCut;
    DirectedGraph residualGraph = m_GraphG1;
    vector<int> dist;
    vector<int> parent;

    residualGraph.BFS(m_StartingVertexG1, dist, parent);

    /// Run BFS as long as there is an improving path.
    while (dist[m_EndingVertexG1 - 1] != INFINITE)
    {
        PostImprovingPathProcedure(m_GraphG1, residualGraph, dist, parent, m_StartingVertexG1, m_EndingVertexG1);
        residualGraph.BFS(m_StartingVertexG1, dist, parent);
    }

    /// Split the vertices to S and T grps and Calculate the maxFlow recieved at the end of the algorithm
    graphMinCut = m_GraphG1.ExtractGraphCut(residualGraph, m_StartingVertexG1, m_EndingVertexG1, dist);

    return graphMinCut;
}

GraphCut MaxFlowProgram::FordFulkersonDijkstra()
{
    GraphCut graphMinCut;
    DirectedGraph residualGraph = m_GraphG2;
    vector<int> dist;
    vector<int> parent;

    residualGraph.Dijkstra(m_StartingVertexG2, dist, parent);

    /// Run Dijkstra as long as there is an improving path.
    while (dist[m_EndingVertexG2 - 1] != INFINITE)
    {
        PostImprovingPathProcedure(m_GraphG2, residualGraph, dist, parent, m_StartingVertexG2, m_EndingVertexG2);
        residualGraph.Dijkstra(m_StartingVertexG2, dist, parent);
    }

    /// Split the vertices to S and T grps and Calculate the maxFlow recieved at the end of the algorithm
    graphMinCut = m_GraphG2.ExtractGraphCut(residualGraph, m_StartingVertexG2, m_EndingVertexG2, dist);

    return graphMinCut;
}

void MaxFlowProgram::UpdateGraphs(DirectedGraph& originalGraph, DirectedGraph& residualGraph, FlowPath& returnedPath)
{
    list<DirectedEdge*>::iterator edgesItr;
    int currSrcVertex, currDstVertex, flowAmount = returnedPath.flowAmount;

    /// In the improving path that found, for each edge update both the original and the residual graph.
    for (edgesItr = returnedPath.pathEdgesList.begin(); edgesItr != returnedPath.pathEdgesList.end(); edgesItr++)
    {
        currSrcVertex = (*edgesItr)->GetSrcVertex();
        currDstVertex = (*edgesItr)->GetDstVertex();
        /// Update procedure in the original graph, for a single edge in the residual path.
        SingleStepOriginalGraphUpdate(originalGraph, flowAmount, currSrcVertex, currDstVertex);
        /// Update procedure in the residual graph, for a single edge in the residual path.
        SingleStepResdiualGraphUpdate(residualGraph, flowAmount, currSrcVertex, currDstVertex);
    }
}

void MaxFlowProgram::SingleStepOriginalGraphUpdate(DirectedGraph& originalGraph, int flowAmount, int srcVertex, int dstVertex)
{
    DirectedEdge* currEdge;
    DirectedEdge* antiParallelEdge; 

    ///Update the flow in the current edge (OrginialGraph), if the edge exist
    currEdge = originalGraph.GetEdge(srcVertex, dstVertex);
    if (currEdge != nullptr)
    {
        currEdge->AddFlow(flowAmount);
    }

    /// if there is anti-parallel edge in the orginal graph -> update as well the flow there.
    antiParallelEdge = originalGraph.GetEdge(dstVertex, srcVertex);
    if (antiParallelEdge != nullptr)
    {
        antiParallelEdge->AddFlow((-1) * (flowAmount));
    }
}

void MaxFlowProgram::SingleStepResdiualGraphUpdate(DirectedGraph& residualGraph, int flowAmount, int srcVertex, int dstVertex)
{
    DirectedEdge* antiParallelEdge;
    DirectedEdge* currEdge;

    /// We want to update the capcity of the edge that found as improving one.
    currEdge = residualGraph.GetEdge(srcVertex, dstVertex);
    currEdge->AddCapcaity((-1) * (flowAmount));
    if (currEdge->GetCapacity() == 0)
    {
        residualGraph.RemoveEdge(srcVertex, dstVertex);
    }

    /// As well as the anti-parallel one.
    antiParallelEdge = residualGraph.GetEdge(dstVertex, srcVertex);
    /// If there isn't anti-Parallel edge -> Add it!
    if (antiParallelEdge == nullptr) 
    {
        residualGraph.AddEdge(dstVertex, srcVertex, flowAmount);
    }

    else /// The anti-parallel edge already exist, so just need to update the residual capacity
    {
        antiParallelEdge->AddCapcaity(flowAmount);
    }
}

///Using the parent array, follow the improving path and insert it to a list of edges.
MaxFlowProgram::FlowPath MaxFlowProgram::ExtractFlowPath(DirectedGraph& residualGraph, vector<int>& parent, int startVertex, int endVertex)
{
    FlowPath resFlowPath;
    int minEdgeCapacity = NONE, currEdgeCapacity, currVertex = endVertex;
    DirectedEdge* currEdge;

    while (currVertex != startVertex)
    {
        currEdge = residualGraph.GetEdge(parent[currVertex - 1], currVertex);
        /// Add the edge to the head of the list so the path will start form the srcVertex.
        resFlowPath.pathEdgesList.push_front(currEdge);
        currEdgeCapacity = currEdge->GetCapacity();
        if (currEdgeCapacity < minEdgeCapacity || minEdgeCapacity == NONE)
        {
            minEdgeCapacity = currEdgeCapacity;
        }

        currVertex = parent[currVertex - 1];
    }

    /// Get the minimum edge capacity and set the flow that improved in every edge
    resFlowPath.flowAmount = minEdgeCapacity;

    return resFlowPath;
}

void MaxFlowProgram::PrintMinCutResult(GraphCut& minCut, Method method)
{

    if (method == Method::BFS)
    {
        cout << "BFS Method: " << endl;
    }

    else /// Dijkstra
    {
        cout << "Greedy Method: " << endl;
    }

    cout << "Max Flow: " << minCut.cutFlow << endl;
    cout << "Min Cut: ";
    minCut.PrintCut();
}

void MaxFlowProgram::PostImprovingPathProcedure(DirectedGraph& originalGraph, DirectedGraph& residualGraph, vector<int>& dist, vector<int>& parent, int startingVertex, int endingVertex)
{
    FlowPath returnedPath;

    returnedPath.pathEdgesList.clear();
    returnedPath.flowAmount = 0;
    returnedPath = ExtractFlowPath(residualGraph, parent, startingVertex, endingVertex);
    UpdateGraphs(originalGraph, residualGraph, returnedPath);
}



