#include <iostream>
using namespace std;

#define SIZE 5

template <class T>
class Stack{
    int top;
    T stk[SIZE];
    public :
        Stack();
        void push(T);
        void pop();
        T peek();
        void traverse();
};

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
void Stack<T> :: pop(){
    if(top == -1){
        cout<<"Empty!";
    }else{
        T popped = stk[top--];
        cout<<"\n"<<popped<<" has been popped from the stack!";
    }
}

template <class T>
void Stack<T> :: traverse(){
    cout<<"\nStack : ";
    for(int i = 0; i <= top; i++){
        cout<<stk[i]<<" ";
    }
    cout<<endl;
}

int main(){

    // Stack<float> L;
    // float val;

    Stack<int> L;
    int val;

    char ch;
    do{
        int k;
        cout<<"\nSTACK MENU     1.Push 2.Pop 3.Traverse";
        cout<<"\nEnter your choice(1-3) : ";
        cin>>k;

        switch(k){
            case 1 :{
                cout<<"\nPUSH";
                cout<<"\nEnter the element you wish to push:\t";
                cin>>val;

                L.push(val);
                 
            }break;

            case 2 :{
                L.pop();
            }break;

            case 3 :{
                L.traverse();
            }break;

            default: cout<<"\nWRONG CHOICE!";
        }

        cout<<"\nDo you wish to continue?(y/n)\t";
        cin>>ch;
    }while(ch == 'y' || ch == 'Y');
    
    return 0;
}





















