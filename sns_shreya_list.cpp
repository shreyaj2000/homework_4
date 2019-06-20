#include <sys/time.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <list>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

constexpr char nicknames[] = "nicknames.txt";
constexpr char links[] = "links.txt";

//Graph class
class Graph {
	int V; // No. of vertices
	list<int> *adj; // Pointer to an array containing adjacency lists

public:
	Graph(int V) { //constructor
		this->V = V;
		adj = new list<int>[V];
	}
	void addEdge(int v, int w){ //adds edge to graph
		adj[v].push_back(w); // Add w to v's list
	}
	void printGraph(); //prints the adjacency list
	bool isReachable(int s,int d); //checks whether there is a path between the vertices
};


void Graph::printGraph() {
	for (int v = 0; v< V; v++) {

	}
}

bool Graph::isReachable(int src,int dest) {

	// Base case
	if (src == dest)
		return true;


	// Mark all vertices as not visited
	bool *visited = new bool[V];
	for (int i=0; i<V; i++) {
		visited[i] = false;
	}

	//Create a queue for BFS
	queue<int> queue;

	//Mark the current node as visited and enqueue it
	visited[src] = true;
	queue.push(src);
	cout<<src<<" -> ";

	//Generate all adjacent vertices of a vertex
	list<int>::iterator i;

	while (!queue.empty()) {

		//Dequeue a vertex from queue and print it
		src = queue.front();
		queue.pop();

		//Get all adjacent vertices of the dequeued verttex
		//If adjacent vertex has not been visited, mark and enqueue
		for (i= adj[src].begin(); i != adj[src].end(); i++) {

			//If adjacent node is destination, return true
			if (*i == dest) {
				cout<<*i<<endl;
				return true;
			}

			//Else, continue with BFS
			if (!visited[*i]) {
				visited[*i] = true;
				queue.push(*i);
				cout<<*i<<" -> ";
			}
		}
	}

	return false;
}

int main() {

	int vertex_count,src,dest,id,id_src,id_dest;
	string name,name_src,name_dest;

	vertex_count = 0;
	id_src = id_dest = -1;

	cout<<"Enter name of source : ";
	cin>>name_src;

	cout<<"Enter name of destination : ";
	cin>>name_dest;

	//accessing files
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


    //count number of nodes
    while (true) {
    	vertex_count++;
    	link_file>>src>>dest;
    	nickname_file>>id>>name;

    	if (name == name_src) {
    		id_src = id;
    	}
    	else if (name == name_dest) {
    		id_dest = id;
    	}
        if (nickname_file.eof())
            break;

        vertex_count++;
    }

    if (id_src == -1 || id_dest == -1)
    	cout<<"nickname not found";

    //create graph
    Graph g(vertex_count);
    while (true) {
    	link_file>>src>>dest;
    	g.addEdge(src,dest);

    	if (link_file.eof())
            break;
    }

    if (g.isReachable(id_src,id_dest)) {
    	cout<<"PATH OBTAINED"<<endl;
    }
    else
    	cout<<"PATH NOT FOUND"<<endl;



	return 0;
}