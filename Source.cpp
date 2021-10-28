#include "graph.h"

Graph::Graph()
{
	Mode = 0;
	V = 0;
	E = 0;
	directed = true;
	list = nullptr;
	matrix = nullptr;
	weighted = true;
}
Graph::Graph(int x,bool dir,bool wei)
{
	E = 0;
	Mode = 0;
	V = x;
	directed = dir;
	list = new vector<pair<int,double>>[x];
	matrix = nullptr;
	weighted = wei;
}
Graph& Graph::operator=(const Graph& g)
{
	this->E = g.E;
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
	E = g.E;
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
		E++;
	}
}
void Graph::AddEdge(int in, int out)
{
	if (in < V && out < V)
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
		E++;
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
	list = nullptr;
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
void Graph::TopSort()
{
	vector<int>sorted;
	vector<bool> visited(V, false);
	

	
	for (int s = 0; s < V; s++)
	{
		if (visited[s] == false)
		{
			visited[s] = true;
			for (auto i = list[s].begin(); i != list[s].end(); i++)
			{
				if (visited[(*i).first] == false)
				{
					TopSort_helper(visited, (*i).first, sorted);
				}
			}
			sorted.push_back(s);
		}
	}
	for (int i = sorted.size() - 1; i >= 0; i--)
	{
		char x = sorted[i] + 97;
		cout << "DODANO:" << x << endl;
	}
}
void Graph::TopSort_helper(vector<bool> &visited,int s,vector<int>&sorted)
{
	visited[s] = true;
	for (auto i = list[s].begin(); i != list[s].end(); i++)
	{
		if (visited[(*i).first] == false)
		{
			TopSort_helper(visited, (*i).first, sorted);
		}
	}
	sorted.push_back(s);
}
pair<vector<double>,vector<int>> Graph::Dijkstra(int s,int e)
{
	vector<double> dist(V,INT_MAX);
	vector<bool>visited(V,false);
	vector<int> prev(V, -1);
	dist[s] = 0;
	priority_queue<pair<int, double>>pq;
	pq.push({ s,0 });
	while (pq.size() != 0)
	{
		pair<int, double> Node = pq.top();
		pq.pop();
		visited[Node.first] = true;
		if (dist[Node.first] < Node.second)
			continue;
		for (auto i = list[Node.first].begin(); i != list[Node.first].end(); i++)
		{
			if (visited[(*i).first] == true)
				continue;
			double newDist = dist[Node.first] + Node.second;
			if (newDist < dist[(*i).first])
			{
				prev[(*i).first] = Node.first;
				pq.push({ (*i).first, Node.second });
				dist[(*i).first] = dist[Node.first] + Node.second;
			}
		}
		if (Node.first == e)
			return{ dist,prev };
	}
	return { dist,prev };
}
vector<int> Graph::DijkstraShortestPathRoad(int s, int e)
{
	pair<vector<double>, vector<int>>wynik = Dijkstra(s, e);
	vector<int>Path;

	if (wynik.first[e] == INT_MAX)
		return Path;
	for (auto i = e; i != -1; i = wynik.second[e])
		Path.push_back(i);
	for (int i = 0; i < Path.size() / 2; i++)
		swap(Path[i], Path[Path.size() - 1 - i]);
	return Path;
}
vector<double> Graph::DijkstraShortestPathDist(int s, int e)
{
	pair<vector<double>, vector<int>>wynik = Dijkstra(s, e);
	vector<double>Path = wynik.first;
	return Path;
}
void Graph::BF(int s)
{
	vector<double>Dist(V,INT_MAX);
	Dist[s] = 0;

		for (int i = 0; i < V - 1; i++)
		{
			for (auto j = list[i].begin(); j != list[i].end(); j++)
			{
				double NewDist = Dist[i] + (*j).second;
				if (NewDist < Dist[(*j).first])
					Dist[(*j).first] = NewDist;
			}
		}
		for (int i = 0; i < V - 1; i++)
		{
			for (auto j = list[i].begin(); j != list[i].end(); j++)
			{
				double NewDist = Dist[i] + (*j).second;
				if (NewDist < Dist[(*j).first])
					Dist[(*j).first] = INT_MIN;
			}
		}
		for (auto x : Dist)
		{
			setprecision(5);
			cout << x << " ";
		}
			
}