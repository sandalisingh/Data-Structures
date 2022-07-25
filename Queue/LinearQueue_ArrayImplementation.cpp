#include <iostream>
using namespace std;

class Queue{
    int front, rear;
    int size;
    int *Q;

    public:
        Queue();
        Queue(int);
        void Enqueue();
        void Dequeue();
        void Display();
};

Queue :: Queue(){
    front = -1;
    rear = -1;
    size = 5;
    Q = new int[size];
}

Queue :: Queue(int size){
    front = -1;
    rear = -1;
    this->size = size;
    Q = new int[this->size];
}

void Queue :: Enqueue() {			
    int val;
    if (rear == size - 1){
        cout<<"\nOVERFLOW!\n"<<endl; 
        return;
    }else {  
        cout<<"Enqueue : "; 
        cin>>val;
        rear++;
        Q[rear] = val;                   
    }							
}

void Queue :: Dequeue() {
    if (front == rear) { 
        cout<<"\nUNDERFLOW!\n"; 
        return ;
	} else {
        cout<<"Dequeue : "<< Q[front + 1] <<endl; 
        front++;
    } 
}
					
void Queue :: Display() {
    if (front == rear){
        cout<<"\nEmpty!\n"<<endl; 
    }else {
        cout<<"Queue : "; 
        for (int i = front + 1; i <= rear; i++) {
            cout<<Q[i]<<" ";
        }
        cout<<endl; 
    }			
}

int main() {
    Queue Q;
	int ch;
    do {
        cout<<"\n\nMENU\n";
        cout<<"1) Insert element to queue"<<endl; 
        cout<<"2) Delete element from queue"<<endl; 
        cout<<"3) Display all the elements of queue"<<endl; 
        cout<<"4) Exit"<<endl;
        cout<<"Enter your choice : "; 
        cin>>ch;
        switch (ch) {
            case 1: Q.Enqueue();
            break;
            case 2: Q.Dequeue();
            break;
            case 3: Q.Display();
            break;
            case 4: cout<<"Exit"<<endl;
            break;
            default: cout<<"Invalid choice"<<endl;                  
        }
    } while(ch!=4); 
    return 0;					
}
			
				
			
			 		