#include "graph.h"


int main()
{
	Graph g(10,true,true);
	g.AddEdge(0, 1, 5);
	g.AddEdge(1, 6, 60);
	g.AddEdge(1, 5, 30);
	g.AddEdge(1, 2, 20);
	g.AddEdge(2, 3, 10);
	g.AddEdge(3, 2, -15);
	g.AddEdge(2, 4, 75);
	g.AddEdge(6, 7, -50);
	g.AddEdge(7, 8, -10);
	g.AddEdge(5, 8, 50);
	g.AddEdge(5, 6, 5);
	g.AddEdge(5, 4, 25);
	g.AddEdge(4, 9, 100);
	g.BF(0);	

	

	
	

	
}
