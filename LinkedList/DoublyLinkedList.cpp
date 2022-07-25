/*
    DOUBLY LINKED LIST
    INSERTION : BEG, END, SPECIFIC
    DELETION  : BEG, END, SPECIFIC
*/

#include<iostream>
using namespace std;

struct Node{    //  NODE : | prev | val | next |
    public:
        int val;
        Node* prev;
        Node* next;
};

class DLL{   
    public:
        Node* head; //pointer to the first Node
        DLL(){
            head = NULL;    //initializing LinkedList with NULL
        }
        void Display();
        void InserAtBeg(int);
        void InserAtEnd(int);
        void DelAtBeg();
        void DelAtEnd();
        ~DLL(){
            delete head;
        }
};

void DLL :: InserAtEnd(int value){
    Node* newNode = new Node();
    newNode->val = value;  //adding element at end;
    newNode->next=NULL;
    if(head == NULL){
        newNode->prev=NULL;
        head = newNode;
    }else{   
        Node* temp;
        temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }   //temp points to the last node
        temp->next = newNode;
        newNode->prev = temp;
        //delete t;
    }
}

void DLL :: InserAtBeg(int value){
    Node* newNode = new Node();
    newNode->val = value;
    newNode->prev = NULL;     
    if( head == NULL ){   //adding element at begining;
        head = newNode;
        newNode->next = NULL;
    }else{
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void DLL :: Display(){
    cout<<"\nDLL : ";
    if(head == NULL){   //linked list is empty
        cout<<"EMPTY!!!!!";
        return;
    }else{
        for(Node* cur = head; cur != NULL ; cur = cur->next){     //until node reaches the last node of the LL
            cout<<cur->val<<" -> ";  //prints the Node value on the console
        }
    } 
}

void DLL :: DelAtBeg(){
    if(head == NULL){
        cout<<"\nEmpty!";
    }else if(head->next == NULL){
        head = NULL;
    }else{
        Node* temp;
        temp = head;
        (temp->next)->prev = NULL;
        head = temp->next;
        delete temp;
    }
}

void DLL :: DelAtEnd(){
    if(head == NULL){
        cout<<"\nEmpty!";
    }else if(head->next == NULL){
        head = NULL;
    }else{
        Node* temp;
        temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }   //temp points to the last node
        (temp->prev)->next = NULL;
        delete temp;
    }
}
 
int main()
{
    DLL L = DLL();
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
                cout<<"\nEnter your choice(1-2) : ";
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





















