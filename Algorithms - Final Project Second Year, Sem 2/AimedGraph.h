#pragma once

#include <vector>
#include <string>
#include <list>
#include "Graph.h"

using namespace std;
class vertex;

class AimedGraph : public Graph
{
	
private:

	vector<int> m_OutDegree;
	// Vector that holds for every vertex in the graph his out degree

	vector<int> m_InDegree;
	// Vector that holds for every vertex in the graph his in degree

public:
	
	//C'tors
	
	AimedGraph(const int i_NumOfVetices);
	
	// Virtual functions // 

	virtual void SetEdge(int i_V1, int i_V2);

	virtual void CreateDegreeArrays();

	virtual bool IsAulerianGraph();

	virtual list<vertex*> FindCircuit(vertex* i_V);
	
	// --------------------- //
	
	AimedGraph* CreateTransposedGraph(); // The function creats the transposed graph 

};
