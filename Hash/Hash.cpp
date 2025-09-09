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

        if(i==size) {
            cout << "\nTable full!";
            return -1;
        }
    }

    return ((index + i)%size) ;
}

int Hash :: QuadraticProbing(int key){
    int index = hashIndex(key);
    int i = 0;
    
    while(H[(index + i*i)%size] != 0){
        i++;

        if(i==size) {
            cout << "\nTable full!";
            return -1;
        }
    }

    return ((index + i*i)%size) ;
}

void Hash :: Insert_LinearProbing(int key){
    int index = hashIndex(key);

    if(H[index] != 0){
        index = LinearProbing(key);
    }

    if(index!=-1) H[index] = key;
}

void Hash :: Insert_QuadraticProbing(int key){
    int index = hashIndex(key);

    if(H[index] != 0){
        index = QuadraticProbing(key);
    }

    if(index!=-1) H[index] = key;
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

        if(i==size) return -1;
    }

    return ((index + i) % size) ;
}

int main() {
    Hash H;
    int option = -1;

    while(option != 5) {
        cout << "\n\n----------------------------------------------------";
        cout << "\n\n\t\tHASH TABLE : MENU";
        cout << "\n1. Insert using Linear Probing";
        cout << "\n2. Insert using Quadratic Probing";
        cout << "\n3. Search key";
        cout << "\n4. Display hash table";
        cout << "\n5. Exit";
        cout << "\n--> Select any one of the above options (1-5) : ";
        cin.sync();
        cin >> option;

        switch(option) {
            cin.sync();
            case 1: {
                int x;
                cout << "\nEnter value to insert (Linear Probing): ";
                cin >> x;
                H.Insert_LinearProbing(x);
            } break;
            case 2: {
                int x;
                cout << "\nEnter value to insert (Quadratic Probing): ";
                cin >> x;
                H.Insert_QuadraticProbing(x);
            } break;
            case 3: {
                int x;
                cout << "\nEnter value to search: ";
                cin >> x;
                int index = H.Search(x);
                if(index != -1)
                    cout << "\nKey " << x << " found at index " << index;
                else
                    cout << "\nKey " << x << " not found!";
            } break;
            case 4: {
                H.Display();
            } break;
            case 5: {
                return 0;
            } break;
            default: cout << "\nWrong option selected !!";
        }
    }
    return 0;
}