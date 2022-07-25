#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
} *front = NULL, *rear = NULL;
					
void enqueue(int x) {
    Node *t = new Node; 
    if (t == NULL)				
        cout << "Queue is full!"; 
    else{
        t->data = x; 
        t->next = NULL;
        if (front == NULL)
            front = rear = t; 
        else
            rear->next = t; 
        rear = t;				
    }
}

void dequeue() {					
    int x = -1;
    Node *p;
    if (front == NULL){
        cout << "Queue is empty!"; 
    }else{
        p = front;				
        front = front->next; 
        x = p->data;
        delete p;				
    }			
}
					
void display() {					
    struct Node *p = front;
    cout << "The elements in the queue are : " << endl; 
    while(p){					
        cout << p->data << " ";					
        p = p->next; 
    }
    cout << endl; 
}
					
int main() {
    int ch;
    do {
        cout<<"\n\nMENU"<<endl; 
        cout << "1. Insert element" << endl;
        cout << "2. Delete element" << endl;
        cout << "3. Display queue elements" << endl; 
        cout << "4. Exit" << endl;
        int choice;
        cout << "\nEnter your choice : ";
        cin >> choice;
        switch (choice){
                case 1:{
                    int x;
                    cout << "Enter the number to be inserted : "; cin >> x;
                    enqueue(x);
                    //display();
                }break;
                case 2: {
                    dequeue(); 
                    //display();
                }break;
                case 3: {
                    display();
                } break;
            }
        } while(ch!=4); 
    return 0;
}
