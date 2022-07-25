//Practice

#include <iostream>
#include <limits.h>
#define I INT_MAX

using namespace std;

class Kruskals{

    public:
        void join(int u, int v, int *set);    
        int find(int u, int *set);

        void KruskalsAlgo(int edges[][9]);
};

void Kruskals :: join(int u , int v, int *set){
    if(set[u] < set[v]){
        set[u] += set[v];
        set[v] = u;
    }else{
        set[v] += set[u];
        set[u] = v;
    }
}

int Kruskals :: find(int u, int *set){
    int x = u, v = 0;

    while(set[x] > 0){
        x = set[x];
    }

    while(u != x){
        v = set[u];
        set[u] = x;
        u = v;
    }

    return x;
}

void Kruskals :: KruskalsAlgo(int edges[][9]){
    //declaring data sets
    int set[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    int included[9] = {0};
    int t[2][6];

    //declaring variables
    int u = 0, v = 0;   //represents edge
    int i = 0, j;   //counters to t[][] and edges[][]
    int k = 0;  //points to min edge
    int min = 65535;    //cost of min edge
    int n = 9;  //

    while( i < 6){  //6 times for selecting (7-1) edges
        min = 65535;

        for(j = 0; j < n; j++){
            if(included[j] == 0 && edges[j][2] < min){
                u = edges[j][0];
                v = edges[j][1];

                min = edges[j][2];

                k = j;
            }
        }

        if(find(u, set) != find(v, set)){
            t[0][i] = u;
            t[1][i] = v;

            join(find(u, set), find(v, set), set);
            
            i++;
        }
        
        included[k] = 1;
    }


    //displaying the min cost spanning tree
    cout<<"\n\n\nKRUSKAL's MIN COST SPANNING TREE\n";
    for(int i = 1; i < 6; i++){
        cout<<"\n( "<<t[0][i]<<" , "<<t[1][i]<<" )"<<"";
    }
    cout<<"\n\n\n";
}

int main(){
    int edges[][9] = {
                {1, 1, 2, 2, 3, 4, 4, 5, 5},
                {2, 6, 3, 7, 4, 5, 7, 6, 7},
                {25, 5, 12, 10, 8, 16, 14, 20, 18}
            };

    Kruskals G;
    G.KruskalsAlgo(edges);
    
    return 0;
}