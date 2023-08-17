#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Exceptions.h"

Graph::Graph(const int i_NumOfVetices)
{
	if (i_NumOfVetices <= 0)
		throw Exceptions("invalid input");

	m_Graph.resize(i_NumOfVetices);
	m_Colors.resize(i_NumOfVetices);
	m_VertexParentInDfsTree.resize(i_NumOfVetices);

	for (int i = 0; i < i_NumOfVetices; ++i)
	{
		m_Graph[i] = new vertex(i + 1);
		
	}

}

Graph::~Graph()
{
	for (int i = 0; i < m_Graph.size(); ++i)
		delete m_Graph[i];
}

void Graph::SetCurrentRoot(const int i_Root)
{
	m_CurrentRoot = i_Root;
}

void Graph::SetMapOfEdges(pair<int, int>i_EdgeKey)
{ 
	if (m_MapOfEdges.find(i_EdgeKey) != m_MapOfEdges.end())
	{
		throw(Exceptions("invalid input"));
	}
	
	else
	{
		m_MapOfEdges.insert({ i_EdgeKey,m_MapOfEdges.size() });
	}
}

vector<vertex*>& Graph::GetGraph() { return m_Graph; }

vector<string>& Graph::GetColorsArray() { return m_Colors; }

vector <int>& Graph::GetVertexParentsArrayInDfsTree() { return m_VertexParentInDfsTree; }

int Graph::GetCurrentRoot() { return m_CurrentRoot; }

void Graph::DFS()
{

	int SizeOfGraph = m_Graph.size();

	for (int i = 0; i < SizeOfGraph; ++i)
	{
		m_Colors[i] = "White";
	}

	for (int j = 0; j < SizeOfGraph; ++j)
	{
		if (m_Colors[j] == "White")
		{
			m_CurrentRoot = j;
			Visit(m_Graph[j]);
		}
	}
}

void Graph::Visit(vertex* i_U)
{
	m_VertexParentInDfsTree[(i_U->GetVertexNum()) - 1] = m_CurrentRoot;
	m_Colors[(i_U->GetVertexNum()) - 1] = "Gray";

	list<edge*>::iterator itrBegin = i_U->GetVertexNeighborsList().begin();
	list<edge*>::iterator itrEnd = i_U->GetVertexNeighborsList().end();

	for (; itrBegin != itrEnd; ++itrBegin)
	{
		if (m_Colors[((*itrBegin)->GetEdgeNum()) - 1] == "White")
		{
			Visit(m_Graph[((*itrBegin)->GetEdgeNum()) - 1]);
		}
	}

	m_Colors[(i_U->GetVertexNum()) - 1] = "Black";

}

list<vertex*> Graph::Euler()
{
	list<vertex*> eulerCircuit = FindCircuit(m_Graph[0]);

	list<vertex*>::iterator itrBegin = eulerCircuit.begin();
	list<vertex*>::iterator itrEnd = eulerCircuit.end();

	for (; itrBegin != itrEnd; ++itrBegin)
	{
		if ((*itrBegin)->GetFirstUnmarkedEdge() != (*itrBegin)->GetVertexNeighborsList().end())
		{
			vertex* FirstVertexInCirciutWithUnmarkedEdges = (*itrBegin);
			list<vertex*> newCircuit = FindCircuit(FirstVertexInCirciutWithUnmarkedEdges);

			AppendLists(eulerCircuit, newCircuit, itrBegin);
		}
	}

	return eulerCircuit;
}

void Graph::AppendLists(list<vertex*>& i_EulerCircuit, list<vertex*>& i_NewCircuit, list<vertex*>::iterator i_ItrBeginEulerCircuit)
{
	list<vertex*>::iterator itrBeginOfNewCircuit = i_NewCircuit.begin();

	i_NewCircuit.erase(itrBeginOfNewCircuit);

	i_EulerCircuit.splice(++(i_ItrBeginEulerCircuit), i_NewCircuit);
}
