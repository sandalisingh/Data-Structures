//g++ -std=c++11 Hash.cpp -o Hash

#include <iostream>
using namespace std;

class Hash{
    int size;
    int *H;

    public:
        Hash();
        Hash(int);

        void Insert_LinearProbing(int key);
        void Insert_QuadraticProbing(int key);

        int hashIndex(int key);

        int LinearProbing(int);
        int QuadraticProbing(int key);

        void Display();

        int Search(int);
};

Hash :: Hash(){
    size = 10;
    H = new int[size];
}

Hash :: Hash(int size){
    this->size = size;
    H = new int[size];
}

int Hash :: hashIndex(int key){
    return (key % 10);
}

int Hash :: LinearProbing(int key){
    int index = hashIndex(key);
    int i = 0;
    
    while(H[(index + i)%size] != 0){
        i++;
    }

    return ((index + i)%size) ;
}

int Hash :: QuadraticProbing(int key){
    int index = hashIndex(key);
    int i = 0;
    
    while(H[(index + i*i)%size] != 0){
        i++;
    }

    return ((index + i*i)%size) ;
}

void Hash :: Insert_LinearProbing(int key){
    int index = hashIndex(key);

    if(H[index] != 0){
        index = LinearProbing(key);
    }

    H[index] = key;
}

void Hash :: Insert_QuadraticProbing(int key){
    int index = hashIndex(key);

    if(H[index] != 0){
        index = QuadraticProbing(key);
    }

    H[index] = key;
}

void Hash :: Display(){
    cout<<"\n\nHash Table : \n";

    for(int i = 0; i < size; i++){
        cout<<i<<"\t";
    }

    cout<<"\n";

    for(int i = 0; i < size; i++){
        cout<<H[i]<<"\t";
    }

    cout<<"\n\n";
}

int Hash :: Search(int key){
    int index = hashIndex(key);

    int i = 0;

    while(H[(index + i) % size] != key){
        i++;
    }

    return ((index + i) % size) ;
}

int main(){
    Hash H;

    // H.Insert_LinearProbing(12);
    // H.Insert_LinearProbing(25);
    // H.Insert_LinearProbing(35);
    // H.Insert_LinearProbing(26);

    H.Insert_QuadraticProbing(23);
    H.Insert_QuadraticProbing(43);
    H.Insert_QuadraticProbing(13);
    H.Insert_QuadraticProbing(27);

    H.Display();

    cout<<"\n\n\n35 found at index "<<H.Search(35)<<"\n\n\n";
    
    return 0;
}
