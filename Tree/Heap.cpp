#include <iostream>
using namespace std;

class Heap{
    int size;
    int *A;

    public:
        Heap();
        Heap(int);

        void Insert(int, int);
        int Delete(int n);
        void HeapSort();
};

Heap :: Heap(){
    size = 10;
    A = new int[10];
}

Heap :: Heap(int n){
    size = n;
    A = new int[n];
}

void Heap :: Insert(int val, int n){    //MAX HEAP
    A[n] = val;
    int temp = A[n];
    int i = n;

    while(i>1 && temp>A[i/2]){
        A[i] = A[i/2];
        i = i/2;
    }

    A[i] = temp;
}

int Heap :: Delete(int n){
    int val = A[1];
    int x = A[n];

    A[1] = A[n];

    int i = 1;
    int j = i * 2;

    while(j < n - 1){
        if(A[j + 1] > A[j]){
            j = j + 1;
        }
        if(A[i] < A[j]){
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;

            i = j;
            j = 2 * j;
        }else{
            break;
        }
    }

    return val;
}

int main(){
    return 0;
}

