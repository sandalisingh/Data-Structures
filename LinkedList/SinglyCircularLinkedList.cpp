//SINGLY CIRCULAR LINKED LIST
// INSERTION & DELETION

#include <iostream>
using namespace std;

struct Node{    
    public:
        int val;
        Node* next;
};

class SCLL{   
    public:
        Node* head; 
        SCLL(){
            head = NULL;    
        }
        void Display();
        void InserAtBeg(int);
        void InserAtEnd(int);
        void DelAtBeg();
        void DelAtEnd();
        ~SCLL(){
            delete head;
        }
};

void SCLL :: Display(){
    cout<<"\nSCLL : ";
    if(head == NULL){   //linked list is empty
        cout<<"EMPTY!";
        return;
    }else{
        Node* cur = head;
        do{     
            cout<<cur->val<<" -> ";  
            cur = cur->next;
        }while(cur != head ); 
        //cout<<cur->val;
    } 
}

void SCLL :: InserAtBeg(int v){ 
    Node* newNode = new Node();
    newNode->val = v; 

    if(head == NULL){   
        head = newNode; 
        newNode->next = head;    
    }else{ 
        newNode->next = head; 

        Node* temp = head;
        while(temp->next != head){   
            temp = temp->next;
        }
        temp->next = newNode;   
       
        head = newNode;  
    }
}

void SCLL :: InserAtEnd(int v){   
    Node* newNode = new Node();
    newNode->val = v;   
    
    if(head == NULL){   
        head = newNode;    
    }else{
        Node* temp = head;
        while(temp->next != head){   
            temp = temp->next;
        }
        temp->next = newNode;   
    }
    
    newNode->next = head;    
}

void SCLL :: DelAtBeg(){
    if(head == NULL){
        cout<<"\nEmpty!";
    }else if((head->next) == head){
        head = NULL;
    }else{
        Node *temp, *cur;
        temp = head;
        cur = head;

        do{
            cur = cur->next;
        }while( (cur->next) != head );

        (cur->next) = (head->next);
        head = (head->next);

        delete temp;
    }
}

void SCLL :: DelAtEnd(){
    if(head == NULL){
        cout<<"\nEmpty!";
    }else if((head->next) == head){
        head = NULL;
    }else{
        Node *cur, *prev;
        cur = head;
        do{
            prev = cur;
            cur = cur->next;
        }while((cur->next) != head);
        prev->next = head;
        delete cur;
    }
}

int main(){
    SCLL L = SCLL();
    char ch;
    do{
        int k;
        cout<<"\nM E N U";
        cout<<"\n1. Insertion";
        cout<<"\n2. Deletion";
        cout<<"\n3. Display";
        cout<<"\nEnter your choice(1-3) : ";
        cin>>k;

        switch(k){
            case 1 :{
                cout<<"\nINSERTION";

                int val;
                cout<<"\nEnter the element you wish to insert:\t";
                cin>>val;

                cout<<"\t1.in the beginning";
                cout<<"\t2.at the end";
                cout<<"\nEnter your choice(1-2) : ";
                cin>>k;

                    switch(k){
                        case 1: {
                            L.InserAtBeg(val);
                        }
                        break;
                        case 2: {
                            L.InserAtEnd(val);
                        }
                        break;
                        default : cout<<"\nWrong input!";
                    }
                 
            }break;

            case 2 :{
                cout<<"\nDELETION";
                cout<<"\t1.from the beginning";
                cout<<"\t2.from the end";
                cout<<"\nEnter your choice(1-3) : ";
                cin>>k;

                    switch(k){
                        case 1: {
                            L.DelAtBeg();
                        }
                        break;
                        case 2: {
                            L.DelAtEnd();
                        }
                        break;
                        default: cout<<"\nWRONG CHOICE!";
                    }

            }break;

            case 3 :{
                L.Display();
            }break;

            default: cout<<"\nWRONG CHOICE!";
        }

        cout<<"\nDo you wish to continue?(y/n)\t";
        cin>>ch;
    }while(ch == 'y' || ch == 'Y');
    
    return 0;
}












