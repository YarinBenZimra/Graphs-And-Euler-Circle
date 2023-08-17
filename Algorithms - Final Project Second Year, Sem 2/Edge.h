#pragma once


// The class represents an edge in the graph //

class edge 
{

private:

	int   m_EdgeNum;
	 // The number that represents the edge

	bool  m_IsEdgeMarked; 
     // boolean that says if we passed this edge

	edge* m_TwinEdge;    
	 // This pointer is for an undirected graph such that the edge (u,v) points to its "twin sister" (v,u)

public:

	// C'tors //

	edge(const int i_EdgeNum = 0, const bool i_IsEdgeMarked = false, edge* i_TwinEdge = nullptr);

	edge(const edge& i_Other) = delete;
	// Deleted Copy C'tor to prevent copying

	// Operators//

	edge& operator=(const edge& i_Other) = delete;
	// Deleted operator= to prevent copying

	// Set Functions // 

	void SetEdgeNum(const int i_EdgeNum);

	void SetIsEdgeMarked(const bool i_IsEdgeMarked);

	void SetTwinEdge(edge* i_TwinEdge);

	// Get Functions //

	int GetEdgeNum() const;

	bool GetIsEdgeMarked() const;
	
	edge* GetTwinEdge() const;
};

