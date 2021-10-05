#define GRAPH_H_
#ifdef GRAPH_H_
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
class Graph
{
private:
    int Mode;//0-List representation, 1-Matrix representation
    int V;
    //LIST    
    /*PROS:Good for sparse graphs, Iterating over all edges is efficient
      CONS:Bad for dense graph(space),Edge weight lookup O(E), more complex representation*/
    vector<pair<int, double>>*list;
    
    //MATRIX    
    /*PROS:Good for dense graph(space),Edge weight lookup O(1), simple representation
      CONS:O(V^2) Space, Iterating over edges O(V^2) */
    vector<double> *matrix;
    bool directed;
    bool weighted;
    void AddListRep();
    void AddMatrixRep();
    void RemoveListRep();
    void RemoveMatrixRep();
    void PrintAdjList();
    void PrintAdjMatrix();

public:
    Graph();
    Graph(int x, bool dir=true, bool wei=true);
    Graph &operator=(const Graph &g);
    Graph(const Graph &g);
    ~Graph();
    void SwitchRepresentation();
    void AddEdge(int in,int out,int weight);
    void AddEdge(int in,int out);
    void PrintGraph();
    void DFS(int s);
    void DFS_helper(bool *visited,int s);
    void FindComponents();
    void DFS_FC(int s, bool* visited, int* component,int &count);
    void BFS(int s);
    int* Path(int s, int e);
    void ReconstructPath(int* path,int s,int e);
    void ShortestPath(int s, int e);
    
};

#endif

