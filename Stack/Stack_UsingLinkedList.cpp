//STACK
//Using Linear Linked List
//Push , Pop , Traverse

#include <iostream>
using namespace std;

struct Node{    
    public:
        int val;
        Node* next;
};

class Stack{
    Node* top;
    public :
        Stack();
        void push(int);
        void pop();
        void traverse();
};

Stack :: Stack(){
    top = NULL;
}

void Stack :: push(int x){
    Node *temp = new Node;
    if(!temp){
        cout<<"\nHeap is full!";
    }else{
        temp->val = x;
        temp->next = top;
        top = temp;
    }
}

void Stack :: pop(){
    if(top == NULL){
        cout<<"Empty!";
    }else{
        Node *temp = top;
        top = top->next;

        int popped = temp->val;
        delete temp;
        cout<<"\n"<<popped<<" has been popped from the stack!";
    }
}

void Stack :: traverse(){
    cout<<"\nStack : ";
    Node *temp = top;
    while(temp != NULL){
        cout<<temp->val<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

int main(){
    Stack L = Stack();
    char ch;
    do{
        int k;
        cout<<"\nSTACK MENU     1.Push 2.Pop 3.Traverse";
        cout<<"\nEnter your choice(1-3) : ";
        cin>>k;

        switch(k){
            case 1 :{
                cout<<"\nPUSH";

                int val;
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





















