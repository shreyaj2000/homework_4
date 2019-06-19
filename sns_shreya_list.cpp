//find path from jacob to gilbert

#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <list>
#include <string.h>

using namespace std;

char nicknames[] = "nicknames.txt";
char links[] = "links.txt";

class Graph 
{ 
    int V;    // No. of vertices 
    list<int> *adj;    // Pointer to an array containing adjacency lists 
public: 
    Graph(int V);  // Constructor 
    void addEdge(int v, int w); // adds an edge to graph 
    bool isReachable(int s, int d); //checks if path exists
    void printGraph(); //prints the list of vertexes and their edges

    void printAllPaths(int s, int d);
    void printAllPathsUtil(int , int , bool [], int [], int &); 
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_back(w); // Add w to v’s list. 
} 


// print adjacency list representation of graph
void Graph::printGraph()
{ 
  for (int v = 0; v < V; ++v) 
  { 
    cout <<"\n"<<v; 
    for (auto x : adj[v]) 
       cout << " ->" << x; 
    printf("\n"); 
  } 
}

bool Graph::isReachable(int s, int d) 
{ 
    // Base case 
    if (s == d) 
      return true; 
  
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // Create a queue for BFS 
    list<int> queue; 
  
    // Mark the current node as visited and enqueue it 
    visited[s] = true; 
    queue.push_back(s); 
  
    // it will be used to get all adjacent vertices of a vertex 
    list<int>::iterator i; 
  
    while (!queue.empty()) 
    { 
        // Dequeue a vertex from queue and print it 
        s = queue.front(); 
        queue.pop_front(); 
  
        // Get all adjacent vertices of the dequeued vertex s 
        // If a adjacent has not been visited, then mark it visited 
        // and enqueue it 
        for (i = adj[s].begin(); i != adj[s].end(); ++i) 
        { 
            // If this adjacent node is the destination node, then  
            // return true 
            if (*i == d)
                return true; 
  
            // Else, continue to do BFS 
            if (!visited[*i]) 
            { 
                visited[*i] = true; 
                queue.push_back(*i); 
            } 
        } 
    } 
      
    // If BFS is complete without visiting d 
    return false; 
}

// Prints all paths from s to d 
void Graph::printAllPaths(int s, int d) 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    cout<<"V = "<<V;
  
    // Create an array to store paths 
    int *path = new int[V]; 
    int path_index = 0; // Initialize path[] as empty 
  
    // Initialize all vertices as not visited 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // Call the recursive helper function to print all paths 
    printAllPathsUtil(s, d, visited, path, path_index); 
}

void Graph::printAllPathsUtil(int u, int d, bool visited[], 
                            int path[], int &path_index) 
{ 
    // Mark the current node and store it in path[] 
    visited[u] = true; 
    path[path_index] = u; 
    path_index++; 
  
    // If current vertex is same as destination, then print 
    // current path[] 
    if (u == d) 
    { 
        for (int i = 0; i<path_index; i++) 
            cout << path[i] << " "; 
        cout << endl; 
          
    } 
    else // If current vertex is not destination 
    { 
        // Recur for all the vertices adjacent to current vertex 
        list<int>::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
            if (!visited[*i]) 
                printAllPathsUtil(*i, d, visited, path, path_index); 
    } 
  
    // Remove current vertex from path[] and mark it as unvisited 
    path_index--; 
    visited[u] = false; 
}


int main() {
    Graph g(49);
    int src,dest,id;
    string name,name1,name2;

    //create vector with the edges
    fstream link_file(links);
    fstream nickname_file(nicknames);

    if (link_file.fail()) {
      cout << "file not found:" << links << endl;
      return 1;
    }

    if (nickname_file.fail()) {
      cout << "file not found:" << nicknames << endl;
      return 1;
    }

    while (true) {
        link_file>>src>>dest;
        nickname_file>>id>>name;
        if (name=="jacob")
            name1 = name;
        if (name=="gilbert")
            name2 = name;
        if (link_file.eof())
            break;

        g.addEdge(src,dest);

    }

    g.printGraph();

    if(g.isReachable(23, 18)) {
        cout<<"\nThere is a path from "<<name1<<" to "<<name2<<endl; 
        //g.printAllPaths(23, 18);
    }
    else
        cout<<"\nPath does not exist.";

}