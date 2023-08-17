#include "Program.h"
#include "AimedGraph.h"
#include "NotAimedGraph.h"
#include "Vertex.h"
#include "Exceptions.h"

Graph* Program::GetInputFromUser()
{
	char isAimed;
	int n, m;

	cout << "Is the graph directed: y/n" << endl;
	cin >> isAimed;
	cin >> n >> m;

	if (n <= 0 || m <= 0 || m > (n * n))
		throw (Exceptions("invalid input"));

	Graph* pGraph = nullptr;

	if (isAimed == 'y')
	{
		pGraph = new AimedGraph(n);

	}

	else if (isAimed == 'n')
	{
		pGraph = new NotAimedGraph(n);
	}

	else
	{
		throw (Exceptions("invalid input"));
	}

	for (int i = 0; i < m; ++i)
	{
		int v1, v2;
		cin >> v1 >> v2;
		pGraph->SetEdge(v1, v2);

	}

	return pGraph;
}

void Program::RunProgram()
{
	try
	{
		Graph* graph = GetInputFromUser();

		if (graph->IsAulerianGraph() == true)
		{
			cout << "The graph is aulerian" << endl;
			list<vertex*> eulerCircle = graph->Euler();
			PrintEulerCircle(eulerCircle);
		}
		else
		{
			cout << "The graph is not aulerian" << endl;
		}
	}

	catch (Exceptions i_Ex)
	{
		cout << i_Ex.what();
	}

}

void Program::PrintEulerCircle(list<vertex*> i_EulerCircle)
{
	auto itrB = i_EulerCircle.begin();
	auto itrE = i_EulerCircle.end();
	for (; itrB != itrE; ++itrB)
	{
		if (itrB == i_EulerCircle.begin())
		{
			cout << '(';
		}

		cout << (*itrB)->GetVertexNum();

		if (itrB != --(i_EulerCircle.end()))
		{
			cout << ",";
		}

		if (itrB == --(i_EulerCircle.end()))
		{
			cout << ')';
		}
	}
}
