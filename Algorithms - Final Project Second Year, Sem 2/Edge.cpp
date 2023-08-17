#include "Edge.h"
#include "Exceptions.h"

edge::edge(const int i_EdgeNum, const bool i_IsEdgeMarked, edge* i_TwinEdge)
{
	SetEdgeNum(i_EdgeNum);
	SetIsEdgeMarked(i_IsEdgeMarked);
	SetTwinEdge(i_TwinEdge);
}

void  edge::SetEdgeNum(const int i_EdgeNum)
{
	if (i_EdgeNum <= 0)
	{
		throw (Exceptions("invalid input"));
	}

	m_EdgeNum = i_EdgeNum;

}

void  edge::SetIsEdgeMarked(const bool i_IsEdgeMarked)
{
	m_IsEdgeMarked = i_IsEdgeMarked;
}

void  edge::SetTwinEdge(edge* i_TwinEdge)
{
	m_TwinEdge = i_TwinEdge;
}

int   edge::GetEdgeNum() const { return m_EdgeNum; }

bool  edge::GetIsEdgeMarked() const { return m_IsEdgeMarked; }

edge* edge::GetTwinEdge() const { return m_TwinEdge; }