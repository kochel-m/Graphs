#include "graph.h"

Graph::Graph()
{
	Mode = 0;
	V = 0;
	directed = true;
	list = nullptr;
	matrix = nullptr;
	weighted = true;
}
Graph::Graph(int x,bool dir,bool wei)
{
	Mode = 0;
	V = x;
	directed = dir;
	list = new vector<pair<int,double>>[x];
	matrix = nullptr;
	weighted = wei;
}
Graph& Graph::operator=(const Graph& g)
{
	this->V = g.V;
	this->Mode = g.Mode;
	this->directed = g.directed;
	this->weighted = g.weighted;
	if (Mode == 0)
	{
		this->list = new vector<pair<int, double>>[V];
		for (int i = 0; i < V; i++)
			this->list[i] = g.list[i];
	}
	else if (Mode == 1)
	{
		this->matrix = new vector<double>[V];
		for (int i = 0; i < V; i++)
			this->matrix[i] = g.matrix[i];
	}
	return *this;

}
Graph::Graph(const Graph& g)
{
	V = g.V;
	Mode = g.Mode;
	directed = g.directed;
	weighted = g.weighted;
	if (Mode == 0)
	{
		list = new vector<pair<int, double>>[V];
		for (int i = 0; i < V; i++)
			list[i] = g.list[i];
		matrix = nullptr;
	}
	else 
	{
		matrix = new vector<double>[V];
		for (int i = 0; i < V; i++)
			matrix[i] = g.matrix[i];
		list = nullptr;
	}
}
Graph::~Graph()
{
	if (Mode == 0)
		RemoveListRep();
	else
		RemoveMatrixRep();
}
void Graph::PrintAdjList()
{
	for (int i = 0; i < V; i++)
	{
		cout << i << "->";
		for (int j = 0; j < list[i].size(); j++)
		{
			cout << " " << list[i][j].first;
			if (weighted == true)
				cout << "(" << list[i][j].second << ")";
			cout<< " ";
			
		}
		cout << endl;
	}
}
void Graph::PrintGraph()
{
	if (Mode == 0)
	{
		cout << "Adjacency list:\n";
		PrintAdjList();
	}
	else if (Mode == 1)
	{
		cout << "Adjacency Matrix:\n";
		PrintAdjMatrix();
	}
	if (directed == false)
	{
		cout << "Graph is undirected\n";
	}
	else 
		cout << "Graph is directed\n";
}
void Graph::PrintAdjMatrix()
{
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	
}
void Graph::AddEdge(int in,int out,int w)
{
	if (weighted == false)
		w = 1;
	if (in < V && out < V)
	{
		if (Mode == 0)
		{
			list[in].push_back({ out,w });
			if (directed == false)
				list[out].push_back({ in,w });
		}
		else if (Mode == 1)
		{
			matrix[in][out] = w;
			if (directed == false)
				matrix[out][in] = w;
		}
	}
}
void Graph::AddEdge(int in, int out)
{
	if (Mode == 0)
	{
		list[in].push_back({ out,1 });
		if (directed == false)
			list[out].push_back({ out,1 });
	}
	else if (Mode == 1)
	{
		matrix[in][out] = 1;
		if (directed == false)
			matrix[out][in] = 1;
	}
}
void Graph::AddListRep()
{
	
	list = new vector<pair<int, double>>[V];
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			if (matrix[i][j] != 0)
			{
				list[i].push_back({ j,matrix[i][j] });
			}
		}
	}
}
void Graph::RemoveListRep()
{
	if (list != nullptr)
	{
		delete[] list;
	}
	list == nullptr;
}
void Graph::RemoveMatrixRep()
{
	if (matrix != nullptr)
	{
			delete[] matrix;
	}
}
void Graph::AddMatrixRep()
{
	matrix = new vector<double>[V];
	for (int j = 0; j < V; j++)
		{
			matrix[j].resize(V);
		}

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < list[i].size(); j++)
		{
			matrix[i][list[i][j].first] = list[i][j].second;
		}
	}
}
void Graph::SwitchRepresentation()
{
	if (Mode == 0)
	{
		AddMatrixRep();
		RemoveListRep();
		Mode = 1;
	}
	else if (Mode == 1)
	{
		AddListRep();
		RemoveMatrixRep();
		Mode = 0;
	}
}
void Graph::DFS(int s)
{
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	visited[s] = true;
	for (auto i = list[s].begin(); i != list[s].end(); i++)
	{
		if (visited[(*i).first] == false)
		{
			DFS_helper(visited,(*i).first);
		}
	}

}
void Graph::DFS_helper(bool* visited, int s)
{
	visited[s] = true;
	for (auto i = list[s].begin(); i != list[s].end(); i++)
	{
		if (visited[(*i).first] == false)
		{
			DFS_helper(visited, (*i).first);
		}
	}
} 
void Graph::DFS_FC(int s, bool* visited, int* component,int &count)
{
	visited[s] = true;
	component[s] = count;
	for (auto i = list[s].begin(); i != list[s].end(); i++)
	{
		if (visited[(*i).first] == false)
		{
			DFS_FC((*i).first, visited, component, count);
		}
	}
}
void Graph::FindComponents()
{
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	int count = 0;
	int* component = new int[V];
	for (int i = 0; i < V; i++)
	{
		if (visited[i] == false)
		{
			count++;
			DFS_FC(i, visited, component, count);
		}
	}
	cout << count<<endl;
	for (int i = 0; i < V; i++)
		cout << i << ":" << component[i] << "\n";
}
void Graph::BFS(int s)
{
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	queue<int>q;
	q.push(s);
	visited[s] = true;
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		for (auto i = list[x].begin(); i != list[x].end(); i++)
		{
			
			if(visited[(*i).first]==false)
			{
				q.push((*i).first); 
				visited[(*i).first] = true;
			}
		}
	}

}
int* Graph::Path(int s, int e)
{
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	int* prev = new int[V];
	for (int i = 0; i < V; i++)
		prev[i] = INT_MIN;
	queue<int>q;
	q.push(s);
	visited[s] = true;
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		for (auto i = list[x].begin(); i != list[x].end(); i++)
		{

			if (visited[(*i).first] == false)
			{
				q.push((*i).first);
				visited[(*i).first] = true;
				prev[(*i).first] = x;
			}
		}
	}
	return prev;
}
void Graph::ReconstructPath(int* prev,int s,int e)
{
	for (int i = e; i != INT_MIN; i = prev[i])
		cout << i << "-> ";
}
void Graph::ShortestPath(int s, int e)
{
	ReconstructPath(Path(s, e), s, e);
}
