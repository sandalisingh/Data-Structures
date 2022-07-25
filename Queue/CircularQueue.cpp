//CIRCULAR QUEUE
//ARRAY IMPLEMENTATION

#include <iostream>
using namespace std;

class Queue{
    int front , rear , size;
    int *Q;

    public:
        Queue();
        Queue(int);
        void Display();
        void Enqueue(int x);
        int Dequeue();
        bool isEmpty();
        bool isFull();
};

Queue :: Queue(){
    size = 5;
    front =  -1;
    rear = -1;
    Q = new int[size];
}

Queue :: Queue(int size){
    this->size = size;
    front =  -1;
    rear = -1;
    Q = new int[size];
}

void Queue :: Display(){  
    if(isEmpty()) {
        cout << "\nEmpty!\n";
        return;
    }
    
    if(rear >= front){
        for(int i = front; i <= rear; i++){
            cout<<Q[i]<<" ";
        }
    }else{
        for(int i = 0; i <= rear; i++){
            cout<<Q[i]<<" ";
        }
        for(int i = rear + 1; i < front; i++){
            cout<<"- ";
        }
        for(int i = front; i < size; i++){
            cout<<Q[i]<<" ";
        }
    }

    cout<<endl;
}

void Queue :: Enqueue(int x){
    if(isFull()){
        cout<<"\nOVERFLOW!\n"<<endl;
    }else{
        if(front == -1){
            front = 0;
        }
        rear = (rear + 1) % size;
        Q[rear]=x;
    }
}

int Queue :: Dequeue(){
    int x = -1;

    if(isEmpty()){
        cout<<"\nUNDERFLOW!\n"<<endl;
    }else {
        x = Q[front];
        
        if(front == rear){  //deleting 1 element
            front = -1;
            rear = -1;  //EMPTY
        }else{
            front = (front + 1) % size;
        }
    }

    return x;
}

bool Queue :: isEmpty(){
    if(front == -1){
        return true;
    }else{
        return false;
    }
}

bool Queue :: isFull(){
    if((rear + 1) % size == front){
        return true;
    }else{
        return false;
    }
}

int main(){
    Queue Q;
    int ch;
    do {
        cout<<"\n\nCQ"; 
        cout << "\t1.Enqueue";
        cout << "\t2.Dequeue";
        cout << "\t3.Display"; 
        cout << "\t4. Exit";
        int choice;
        cout << "\nChoice : ";
        cin >> choice;
        switch (choice){
                case 1:{
                    int insert;
                    cout << "\nEnqueue : "; 
                    cin >> insert;
                    Q.Enqueue(insert);
                }break;
                case 2:{
                    int del = Q.Dequeue(); 
                    if(del != -1){
                        cout << "\nDequeue : "<<del;
                    }
                }break;
                case 3:{
                    Q.Display();
                } break;
                case 4: return 0;
                default:{
                    cout<<"\nWRONG!\n";
                }
            }
        } while(true); 
    return 0;
}