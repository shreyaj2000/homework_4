//Vertex that takes the most number of steps from given source 

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

constexpr char pages[] = "pages.txt";
constexpr char links[] = "link_wiki.txt";

int counter,max_counter;

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
	bool no_of_steps(int s,int d); //checks whether there is a path between the vertices
	bool check_counter(); //checks if the counter is more than max counter
};

bool Graph::no_of_steps(int src,int dest) {

	counter = 0;

	// Base case
	if (src == dest) {
		counter++;
		return true;
	}


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
	counter++;

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
				return true;
			}

			//Else, continue with BFS
			if (!visited[*i]) {
				visited[*i] = true;
				queue.push(*i);
				counter++;
			}
		}
	}

	return false;
}

bool Graph:: check_counter() {
	if (counter>max_counter) {
		max_counter = counter;
		return true;
	}
	return false;
}

int main() {

	int vertex_counter,src,dest,id,id_src,id_dest;
	string name,name_src;

	int run_num = 0;

	vertex_counter = 0;
	id_src = id_dest = -1;

	cout<<"Enter name of source : ";
	cin>>name_src;

	//opening files
	fstream link_file(links);
	fstream page_file(pages);

    if (link_file.fail()) {
      cout << "file not found:" << links << endl;
      return 1;
    }

    if (page_file.fail()) {
      cout << "file not found:" << pages << endl;
      return 1;
    }


    //counter number of vertices
    while (true) {
    	page_file>>id>>name;

    	if (name == name_src) {
    		id_src = id;
    	}
        if (page_file.eof())
            break;

        vertex_counter++;
    }

    if (id_src == -1)
    	cout<<"page not found";

    //create graph
    Graph g(vertex_counter);
    while (true) {
    	link_file>>src>>dest;
    	g.addEdge(src,dest);

    	if (link_file.eof())
            break;
    }

    page_file.clear();
    page_file.seekg(0,ios::beg);

    //Check each path from source to find the farthest
    while (true) {
    	page_file>>id>>name;

	    if (g.no_of_steps(id_src,id)) {
	    	if(g.check_counter())
	    		id_dest = id;
	    }

    	if (page_file.eof())
            break;
        run_num++;
    }

    //find the destination name of farthest vertex

    string name_dest;

    page_file.clear();
    page_file.seekg(0,ios::beg);

    while (true) {
    	page_file>>id>>name;
    	vertex_counter++;

    	if (id_dest == id) {
    		name_dest = name;
    	}
        if (page_file.eof())
            break;

    }

    cout<<"Farthest point from "<<name_src<<" is "<<name_dest<<endl;
    cout<<"Has a distance of "<<max_counter<<" edges"<<endl;

	return 0;
}
