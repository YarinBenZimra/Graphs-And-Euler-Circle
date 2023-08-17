#include "AimedGraph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Exceptions.h"



AimedGraph::AimedGraph(const int i_NumOfVetices) : Graph(i_NumOfVetices)
{
	m_OutDegree.resize(i_NumOfVetices);
	m_InDegree.resize(i_NumOfVetices);
}

void AimedGraph::SetEdge(int i_V1, int i_V2)
{
	int numOfVertices = GetGraph().size();
	if (i_V1 <= 0 || i_V2 <= 0 || i_V1 > numOfVertices || i_V2 > numOfVertices || i_V1 == i_V2)
		throw(Exceptions("invalid input"));


	auto newKey = make_pair(i_V1, i_V2);

	SetMapOfEdges(newKey);


	vector<vertex*> graph = GetGraph();


	edge* newEdge = new edge(i_V2);

	graph[i_V1 - 1]->GetVertexNeighborsList().push_back(newEdge);

	if (graph[i_V1 - 1]->GetVertexNeighborsList().size() == 1)
	{
		graph[i_V1 - 1]->SetFirstUnmarkedEdge(graph[i_V1 - 1]->GetVertexNeighborsList().begin());
	}


}

void AimedGraph::CreateDegreeArrays()
{

	vector<vertex*> graph = GetGraph();

	for (int i = 0; i < graph.size(); ++i)
	{
		m_OutDegree[i] = graph[i]->GetVertexNeighborsList().size();

		list<edge*>::iterator itrBegin = (*(graph.begin() + i))->GetVertexNeighborsList().begin();
		list<edge*>::iterator itrEnd = (*(graph.begin() + i))->GetVertexNeighborsList().end();

		for (; itrBegin != itrEnd; ++itrBegin)
		{
			++(m_InDegree[((*itrBegin)->GetEdgeNum()) - 1]);
		}
	}
}

bool AimedGraph::IsAulerianGraph()
{
	int SizeOfGraph = GetGraph().size();

	CreateDegreeArrays();

	for (int i = 0; i < SizeOfGraph; ++i)
	{
		if (m_InDegree[i] != m_OutDegree[i])
			return false;
	}

	AimedGraph* transposedGraph = CreateTransposedGraph();

	DFS();
	transposedGraph->DFS();

	vector<int> VertexParentInDfsTreeOfG = GetVertexParentsArrayInDfsTree();
	vector<int> VertexParentInDfsTreeOfGtransposed = transposedGraph->GetVertexParentsArrayInDfsTree();

	for (int i = 0; i < SizeOfGraph - 1; ++i)
	{
		if (VertexParentInDfsTreeOfG[i] != VertexParentInDfsTreeOfG[i + 1]
			|| VertexParentInDfsTreeOfGtransposed[i] != VertexParentInDfsTreeOfGtransposed[i + 1])
			return false;
	}

	delete transposedGraph;

	return true;

}

list<vertex*> AimedGraph::FindCircuit(vertex* i_V)
{
	list< vertex*> circle;

	vertex* v = i_V;
	circle.push_back(v);

	while (v->GetFirstUnmarkedEdge() != v->GetVertexNeighborsList().end())
	{
		list<edge*>::iterator FirstUnmarkedEdge = v->GetFirstUnmarkedEdge();

		vertex* vNeighbor = GetGraph()[((*FirstUnmarkedEdge)->GetEdgeNum()) - 1];
		(*(FirstUnmarkedEdge))->SetIsEdgeMarked(true);

		while (FirstUnmarkedEdge != v->GetVertexNeighborsList().end() && (*FirstUnmarkedEdge)->GetIsEdgeMarked() == true)
		{
			++FirstUnmarkedEdge;
		}

		v->SetFirstUnmarkedEdge(FirstUnmarkedEdge);

		circle.push_back(vNeighbor);

		v = vNeighbor;

	}

	return circle;
}

AimedGraph* AimedGraph::CreateTransposedGraph()
{
	vector<vertex*> graph = GetGraph();

	AimedGraph* transposedGraph = new AimedGraph(graph.size());

	for (int i = 0; i < graph.size(); ++i)
	{
		list<edge*>::iterator itrBegin = (*(graph.begin() + i))->GetVertexNeighborsList().begin();
		list<edge*>::iterator itrEnd = (*(graph.begin() + i))->GetVertexNeighborsList().end();

		for (; itrBegin != itrEnd; ++itrBegin)
		{
			edge* newEdge = new edge(i + 1);
			transposedGraph->GetGraph()[((*itrBegin)->GetEdgeNum()) - 1]->GetVertexNeighborsList().push_back(newEdge);
		}
	}

	return transposedGraph;

}



