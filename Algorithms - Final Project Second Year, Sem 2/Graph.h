#pragma once

#include <vector>
#include <string>
#include <list>
#include <unordered_map>
#include <utility>

// The class represents the whole graph // 

using namespace std;
class vertex;


class Graph
{

public:

    // Function object implementation for unorderd map 

	struct pair_hash 
	{
		template<class T1, class T2>
		 size_t operator () (const pair<T1, T2>& p) const 
		 {
			auto h1 = hash<T1>{}(p.first);
			auto h2 = hash<T2>{}(p.second);
			return h1 ^ h2;
		}
	};

	struct pair_equal 
	{
		template<class T1, class T2>
		bool operator () (const pair<T1, T2>& p1, const pair<T1, T2>& p2) const 
		{
			return p1.first == p2.first && p1.second == p2.second;
		}
	};


    // C'tors //

	Graph(const int i_NumOfVetices);

	~Graph();

	// Set Functions //

	void SetMapOfEdges(pair<int, int> i_EdgeKey);

	void SetCurrentRoot(const int i_Root);

	// Get Functions //

	vector<vertex*>& GetGraph();

	vector<string>& GetColorsArray();

	vector <int>& GetVertexParentsArrayInDfsTree();

	int GetCurrentRoot();

	// Virtual Functions // 

	virtual void SetEdge(int i_V1, int i_V2) = 0;
	// The function checks if the edge (i_V1, i_V2) exists in the graph, the function adds it if it doesn't exist

	virtual void CreateDegreeArrays() = 0;
	// The function creats an array of integers that holds for every vertex it's degree

	virtual bool IsAulerianGraph() = 0;
	// The function checks if the graph aulerian

	virtual list<vertex*> FindCircuit(vertex* i_V) = 0;

	// ------------------------------ //

	void DFS(); 
     
	void Visit(vertex* i_U);

	list<vertex*> Euler();

	void AppendLists(list<vertex*>& i_EulerCircuit, list<vertex*>& i_NewCircuit, list<vertex*>::iterator i_ItrBeginEulerCircuit);
	// The functions concatenates two lists to one from the iterator i_ItrBeginEulerCircuit and onward, 
	// every list represents a circle in the graph 
	

private:

	unordered_map<pair<int, int>, int, pair_hash, pair_equal> m_MapOfEdges;
	// Unordered map is used to create O(n) efficiency for checking the input integrity of the arcs

	vector<vertex*>                                           m_Graph;  
	// Vector of pointers to vertices that represents the graph

	vector<string>                                            m_Colors;
	// Vector that represents the current color of a vertex for the DFS algorythm

	vector <int>                                              m_VertexParentInDfsTree;
	// Vector that holds for every vertex in the graph who his ancest parent in the DFS tree

	int                                                       m_CurrentRoot;
	// Variable that says for every recursive call in the Visit function who the ancest parent of the current vertex in the DFS tree
};
