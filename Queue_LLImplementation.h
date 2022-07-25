#include <iostream>
using namespace std;

#ifndef Queue_LLImplementation_h
#define Queue_LLImplementation_h

template <class T>
class Node{
    public:
        Node *Lchild;
        T data;
        Node *Rchild;
        Node(T x) {
            Lchild = NULL;
            Rchild = NULL;
            data = x;
        }
        Node() {
            Lchild = NULL;
            Rchild = NULL;
            data = NULL;
        }
};

template <class T>
class Queue{
    private:
        int front, rear;
        int size;
        Node<T> **Q;

    public:
        Queue();
        Queue(int size);
        void Enqueue(Node<T> *x);
        void Enqueue(T x);
        T DequeueType();
        Node<T>* DequeueNode();
        void Display();
        bool isEmpty();
};

template <class T>
Queue<T> :: Queue(){
    front = -1;
    rear = -1;
    size = 5;
    Q = new Node<T>*[size];
}

template <class T>
Queue<T> :: Queue(int size){
    front = -1;
    rear = -1;
    this->size = size;
    Q = new Node<T>*[this->size];
}

template <class T>
void Queue<T> :: Enqueue(Node<T> *x){
    if (rear == size - 1){
        cout<<"Queue Overflow"<<endl; 
    }else{ 
        rear++;
        Q[rear] = x;                   
    }	
}

template <class T>
void Queue<T> :: Enqueue(T x){
    if (rear == size - 1){
        cout<<"Queue Overflow"<<endl; 
    }else{ 
        rear++;
        Node<T>* X = new Node<T>(x);
        Q[rear] = X;                   
    }	
}

template <class T>
T Queue<T> :: DequeueType(){
    Node<T>* x = NULL;
    if (front == rear) { 
        cout<<"Queue Underflow "; 
	} else {
        x = Q[front+1];
        front++;					
    } 
    return x->data;
}

template <class T>
Node<T>* Queue<T> :: DequeueNode(){
    Node<T>* x = NULL;
    if (front == rear) { 
        cout<<"Queue Underflow "; 
	} else {
        x = Q[front+1];
        front++;					
    } 
    return x;
}

template <class T>
void Queue<T> :: Display(){
    if (front == - 1)
        cout<<"Queue is empty"<<endl; 
    else {
        cout<<"Queue elements are : "; 
        for (int i = front; i <= rear; i++){
            cout<<Q[i]<<" ";
        } 
        cout<<endl; 
    }
}

template <class T>
bool Queue<T> :: isEmpty(){
    return (front == rear);
}

#endif 