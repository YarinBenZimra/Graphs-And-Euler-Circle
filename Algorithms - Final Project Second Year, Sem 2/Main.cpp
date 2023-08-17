#include "Program.h"

/*
The following program accepts a directed / undirected graph, and returns whether there is an Euler circle in the graph,
that is means, the graph is Eulerian.
If so, the function will return the Euler circuit.

Efficiency of the program : O(n + m) where n represents the number of vertices and m represents the number of arcs.

Program activation instructions :
1. )  The program will ask if the graph is directed or if the graph is undirected.
1.1)  Please enter y for a directed graph or n for an undirected graph.
2. )  Please enter the number of vertices and after institute press enter.
2.1)  Please enter the number of arcs and then press enter.
3. )  Insert pairs of arcs from the group { 1,2,3,....,n } and after each pair press enter, for example:
     
     (u1, v1)
     (u2, v2)
        .
        .
        .
     (um, vm)

4.) If the graph is Eulerian, the Euler circle of the graph will now be printed.
*/



int main()
{
	Program::RunProgram();
	return 0;
}
