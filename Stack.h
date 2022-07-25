#include <iostream>
using namespace std;

#ifndef Stack_h
#define Stack_h


#define SIZE 10

template <class T>
class Stack{
    int top;
    T stk[SIZE];
    public :
        Stack();
        void push(T);
        T pop();
        T peek();
        void traverse();
        bool isEmpty();
};

template <class T>
bool Stack<T> :: isEmpty(){
    return (top == -1);
}

template <class T>
Stack<T> :: Stack(){
    top = -1;
}

template <class T>
void Stack<T> :: push(T x){
    if(top == SIZE-1){
        cout<<"\nHeap is full!";
    }else{
        top++;
        stk[top] = x;
    }
}

template <class T>
T Stack<T> :: pop(){
    T popped = NULL;

    if(top == -1){
        cout<<"Empty!";
    }else{
        popped = stk[top--];
        //cout<<"\n"<<popped<<" has been popped from the stack!";
    }

    return popped;
}

template <class T>
T Stack<T> :: peek(){
    return stk[top];
}

template <class T>
void Stack<T> :: traverse(){
    cout<<"\nStack : ";
    for(int i = 0; i <= top; i++){
        cout<<stk[i]<<" ";
    }
    cout<<endl;
}

#endif 