#include "NotAimedGraph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Exceptions.h"

NotAimedGraph::NotAimedGraph(const int i_NumOfVetices) : Graph(i_NumOfVetices)
{
	m_Degree.resize(i_NumOfVetices);
}

void NotAimedGraph::SetEdge(int i_V1, int i_V2)
{
	int numOfVertices = GetGraph().size();
	if (i_V1 <= 0 || i_V2 <= 0 || i_V1 > numOfVertices || i_V2 > numOfVertices || i_V1 == i_V2)
		throw(Exceptions("invalid input"));

	vector<vertex*> graph = GetGraph();

	list<edge*>::iterator itrBegin = graph[i_V1 - 1]->GetVertexNeighborsList().begin();
	list<edge*>::iterator itrEnd = graph[i_V1 - 1]->GetVertexNeighborsList().end();

	for (; itrBegin != itrEnd; ++itrBegin)
	{
		if ((*itrBegin)->GetEdgeNum() == i_V2)
			throw (Exceptions("invalid input"));

	}

	edge* newEdgeV2ToV1 = new edge(i_V1);
	edge* newEdgeV1ToV2 = new edge(i_V2);

	newEdgeV2ToV1->SetTwinEdge(newEdgeV1ToV2);
	newEdgeV1ToV2->SetTwinEdge(newEdgeV2ToV1);

	graph[i_V1 - 1]->GetVertexNeighborsList().push_back(newEdgeV1ToV2);
	graph[i_V2 - 1]->GetVertexNeighborsList().push_back(newEdgeV2ToV1);

	if (graph[i_V1 - 1]->GetVertexNeighborsList().size() == 1)
	{
		graph[i_V1 - 1]->SetFirstUnmarkedEdge(graph[i_V1 - 1]->GetVertexNeighborsList().begin());
	}

	if (graph[i_V2 - 1]->GetVertexNeighborsList().size() == 1)
	{
		graph[i_V2 - 1]->SetFirstUnmarkedEdge(graph[i_V2 - 1]->GetVertexNeighborsList().begin());
	}


}

void NotAimedGraph::CreateDegreeArrays()
{
	vector<vertex*> graph = GetGraph();

	for (int i = 0; i < graph.size(); ++i)
	{
		m_Degree[i] = graph[i]->GetVertexNeighborsList().size();
	}
}

list<vertex*> NotAimedGraph::FindCircuit(vertex* i_V)
{
	list< vertex*> circle;

	vertex* v = i_V;
	circle.push_back(v);

	while (v->GetFirstUnmarkedEdge() != v->GetVertexNeighborsList().end())
	{
		list<edge*>::iterator FirstUnmarkedEdge = v->GetFirstUnmarkedEdge();

		vertex* vNeighbor = GetGraph()[((*FirstUnmarkedEdge)->GetEdgeNum()) - 1];

		list<edge*>::iterator FirstUnmarkedTwinEdge = vNeighbor->GetFirstUnmarkedEdge();

		(*(FirstUnmarkedEdge))->SetIsEdgeMarked(true);
		(*(FirstUnmarkedEdge))->GetTwinEdge()->SetIsEdgeMarked(true);

		while (FirstUnmarkedEdge != v->GetVertexNeighborsList().end() && (*FirstUnmarkedEdge)->GetIsEdgeMarked() == true)
		{
			++FirstUnmarkedEdge;
		}

		while (FirstUnmarkedTwinEdge != vNeighbor->GetVertexNeighborsList().end() && (*FirstUnmarkedTwinEdge)->GetIsEdgeMarked() == true)
		{
			++FirstUnmarkedTwinEdge;
		}

		v->SetFirstUnmarkedEdge(FirstUnmarkedEdge);
		vNeighbor->SetFirstUnmarkedEdge(FirstUnmarkedTwinEdge);

		circle.push_back(vNeighbor);

		v = vNeighbor;

	}

	return circle;
}

bool NotAimedGraph::IsAulerianGraph()
{
	int SizeOfGraph = GetGraph().size();

	CreateDegreeArrays();

	for (int i = 0; i < SizeOfGraph; ++i)
	{
		if (m_Degree[i] % 2 != 0)
			return false;
	}

	DFS();

	vector<int> VertexParentInDfsTreeOfG = GetVertexParentsArrayInDfsTree();


	for (int i = 0; i < SizeOfGraph - 1; ++i)
	{
		if (VertexParentInDfsTreeOfG[i] != VertexParentInDfsTreeOfG[i + 1])
			return false;
	}

	return true;

}
