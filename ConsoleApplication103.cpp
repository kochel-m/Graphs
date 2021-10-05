#include "graph.h"


int main()
{
	Graph g(15,false,false);
	g.AddEdge(0, 1, 10);
	g.AddEdge(0, 9, 1);
	g.AddEdge(9, 8, 1);
	g.AddEdge(1, 8, 2);
	g.AddEdge(8, 7, 3);
	g.AddEdge(2, 3, 4);
	g.AddEdge(4, 3, 4);
	g.AddEdge(5, 3, 4);
	g.AddEdge(7, 3, 9);
	g.AddEdge(5, 6, 9);
	g.AddEdge(7, 6, 9);
	g.AddEdge(7, 10, 9);
	g.AddEdge(7, 11, 9);
	g.AddEdge(10, 11, 9);
	g.AddEdge(13, 14, 0);

	g.PrintGraph();
	g.ShortestPath(7,0);

	
}
