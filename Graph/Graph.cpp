#include <iostream>
#include "../Queue_LLImplementation.h"

using namespace std;

class Graph{
    int n;  //no of vertices
    int **A;  //Adjacency Matrix

    public:
        Graph();

        void input_AdjacencyMatrix();

        void BFS(int i);   //Breadth Firs tSearch
        void DFS(int u);    //Depth first Search
};

Graph :: Graph(){
    cout<<"\nNumber of Vertices : ";
    cin>> n;
    
    //creating a matrix using pointers
    A = new int*[n + 1];
    for(int i = 0; i <= n; i++){
        A[i]= new int[n + 1];
    }

    input_AdjacencyMatrix();
}

void Graph :: input_AdjacencyMatrix(){
    for(int u = 1; u <= n; u++){
        for(int v = 1; v <= n; v++){
            int k;
            cout<<"\nEgde ("<<u<<", "<<v<<") : ";
            cin>>k;

            A[u][v] = k;
        }
    }
}

void Graph :: BFS(int start){   // start is starting vertex
    cout<<"\n\nBFS : ";

    int *visited = new int[n + 1];  //1 for visited vertex & 0 for not visited vertex
    Queue<int> Q;    //for storing the vertex whose adjacent vertices have to be explored

    cout<<start<<" ";

    visited[start] = 1; //marking as visited
    Q.Enqueue(start);

    while(!Q.isEmpty()){
        int u = Q.DequeueType();    //next vertex to be explored

        for(int v = 1; v <= n; v++){    //exploring all its adjacent vertices
            if(A[u][v] == 1 && visited[v] == 0){    //has an edge and not visited
                cout<<v<<" ";
                visited[v] = 1; //marked as visited
                Q.Enqueue(v);   //enqueuing in queue to explore itts vertices later
            }
        }
    }

    cout<<"\n\n";
}

void Graph :: DFS(int u){ // u is starting vertex
    static int *visited = new int[n];

    if(visited[u] == 0){    //vertex is not visited
        cout<<u<<" ";
        visited[u] = 1;     //marking the vertex as visited

        for(int v = 1; v <= n; v++){    //
            if(A[u][v] == 1 && visited[v] == 0){   //theres an edge & vertex is not visited 
                DFS(v);
            }
        }
    }
}

int main(){
    Graph G;    //number of vertices = 6
    /*
    0 1 1 0 0 0
    1 0 0 1 0 0
    1 0 0 1 0 0
    0 1 1 0 1 1
    0 0 0 1 0 0
    0 0 0 1 0 0
    */

    G.BFS(1);   //1 2 3 4 5 6
    G.BFS(4);   //4 2 3 5 6 1

    cout<<"\n\n\nDFS : ";
    G.DFS(4);   //4 2 1 3 5 6
    cout<<"\n\n\n";

    return 0;
}