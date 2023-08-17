#pragma once

#include <list>

using namespace std;
class edge;

// The class represents an vertex in the graph //

class vertex
{
private:

	list<edge*>::iterator m_FirstUnmarkedEdge;
	// An iterator for the first edge that comes outfrom this vertex that we didn't passed through it

	int                   m_VertexNum;
	// The number that represents the vertex
	
	list<edge*>           m_VertexNeighborsList;
	// A list of pointers to all the edges that points this vertex
	

public:
	
	// C'tors //

	vertex(const int i_VertexNum = 0);

	vertex(const edge& i_Other) = delete;
	// Deleted Copy C'tor to prevent copying

	// Operators //

	vertex& operator=(const edge& i_Other) = delete;
	// Deleted operator= to prevent copying
	
	~vertex();
	
	// Set Functions // 

	void SetVertexNum(const int i_VertexNum);

	void SetFirstUnmarkedEdge(list<edge*>::iterator i_FirstUnmarkedEdge);

	// Get Functions // 

	int GetVertexNum() const;

	list<edge*>::iterator GetFirstUnmarkedEdge() const;

	list<edge*>& GetVertexNeighborsList();
};

