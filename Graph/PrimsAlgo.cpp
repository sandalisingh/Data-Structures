//Practice

#include <iostream>
#include <limits.h>
#define I INT_MAX

using namespace std;

class Prims{

    public:
        void PrimsAlgo(int cost[][8]);
};

void Prims :: PrimsAlgo(int cost[][8]){
    int min = I;
    int n = 7;
    int near[8];
    int t[2][6];    //represents the edges of the spanning tree
    int u, v;

    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++){    //finding the min cost in the upper triangluar of the matrix
            if(cost[i][j] < min){
                min = cost[i][j];
                u = i;
                v = j;
            }
        }
    }

    t[0][0] = u;    //assigning the edge to the spanning tree
    t[1][0] = v;

    near[u] = near[v] = 0;  //mark the vertices as visited

    //for the 1st pair of vertices (u,v)
    //scan the matrix
    //which vertex is nearer to which u/v
    for(int i = 1; i <= n; i++){
        if(near[i] != 0){   //vertex is not taken
            if(cost[i][u] < cost[i][v]){
                near[i] = u;    //i th vertex is nearer to u
            }else{
                near[i] = v;    //i th vertex is nearer to v/ both at infinity
            }
        }
    }


    for(int i = 1; i <= n-2; i++){  //2 vertices have already been taken
        min = I;
        int k;

        for(int j = 1; j <= n; j++){
            if(near[j] != 0 && cost[j][near[j]] < min){
                //in the nearest to that index vertex array
                //find the min cost
                //and assign that edge to the min cost spanning tree matrix
                k = j;
                min = cost[j][near[j]];
            }
        }

        //assigning that edge to the min cost spanning tree matrix
        t[0][i] = k;
        t[1][i] = near[k];

        near[k] = 0;    //marking that vertex as taken

        for(int j = 1; j <= n; j++){
            if(near[j] != 0 && cost[j][k] < cost[j][near[j]]){
                near[j] = k;    //updating the nearest vertex to that index vertex array
            }
        }
    }

    //displaying the min cost spanning tree
    cout<<"\n\n\nPRIMS's MIN COST SPANNING TREE\n";
    for(int i = 1; i < n-1; i++){
        cout<<"\n( "<<t[0][i]<<" , "<<t[1][i]<<" )"<<"";
    }
    cout<<"\n\n\n";
}

int main(){
    int cost[][8] = {
                {I, I,  I,  I,  I,  I,  I,  I},
                {I, I,  25, I,  I,  I,  5,  I},
                {I, I,  12, I,  8,  I,  I,  I},
                {I, I,  I,  8,  I,  16, I,  14},
                {I, I,  I,  I,  16, I,  20, 18},
                {I, 5,  I,  I,  I,  20, I,  I},
                {I, I,  10, I,  14, 18, I,  I}
            };

    Prims G;
    G.PrimsAlgo(cost);
    
    return 0;
}