#pragma once

#include <iostream>
#include <list>

using namespace std;
class Graph;
class vertex;

class Program
{
public:

	static Graph* GetInputFromUser();

	static void RunProgram();

	static void PrintEulerCircle(list<vertex*> i_EulerCircle);

};
