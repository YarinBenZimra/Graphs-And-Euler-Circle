#pragma once


#include <vector>
#include <string>
#include <list>
#include "Graph.h"

// Class that represents a notaimed graph

using namespace std;
class vertex;

class NotAimedGraph : public Graph
{

private:

	vector<int> m_Degree;
	// Vector that holds for every vertex in the graph his degree


public:
	
	// C'tors //

	NotAimedGraph(const int i_NumOfVetices);
	
	// Virtual Functions //

	virtual void SetEdge(int i_V1, int i_V2);

	virtual void CreateDegreeArrays();

	virtual list<vertex*> FindCircuit(vertex* i_V);

	virtual bool IsAulerianGraph();
};
