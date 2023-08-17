#include "Vertex.h"
#include "Edge.h"
#include "Exceptions.h"

vertex::vertex(const int i_VertexNum)
{
	SetVertexNum(i_VertexNum);
}

vertex::~vertex()
{
	list<edge*>::iterator itrBegin = m_VertexNeighborsList.begin();
	list<edge*>::iterator itrEnd = m_VertexNeighborsList.end();

	for (; itrBegin != itrEnd; ++itrBegin)
		delete (*itrBegin);
}

void vertex::SetVertexNum(const int i_VertexNum)
{
	if (i_VertexNum <= 0)
	{
		throw (Exceptions("invalid input"));
	}
	m_VertexNum = i_VertexNum;
}

void vertex::SetFirstUnmarkedEdge(list<edge*>::iterator i_FirstUnmarkedEdge) { m_FirstUnmarkedEdge = i_FirstUnmarkedEdge; }

int vertex::GetVertexNum() const { return m_VertexNum; }

list<edge*>::iterator vertex::GetFirstUnmarkedEdge() const { return m_FirstUnmarkedEdge; }

list<edge*>& vertex::GetVertexNeighborsList() { return m_VertexNeighborsList; }