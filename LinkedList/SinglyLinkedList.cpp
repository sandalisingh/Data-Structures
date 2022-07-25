/*
    SINGLY LINKED LIST
    INSERTION : BEG, END, SPECIFIC
    DELETION  : BEG, END, SPECIFIC
*/

#include <iostream>
using namespace std;

struct Node{    //  NODE : | val | pointer to the next node |
    public:
        int val;
        Node* next;
};

class LinkedList{   //LinkedList :  Head(pointer to the first Node)-> 1stNode->2nd->...
    int size;   //size of the LinkedList/ Total number of nodes
    public:
        Node* head; //pointer to the first Node
        LinkedList(){
            head = NULL;    //initializing LinkedList with NULL
        }
        void Display();
        void BubbleSort();
        void InserAtBeg(int);
        void InserAtEnd(int);
        void Del(int);
        void DelAtBeg();
        void DelAtEnd();
        void Inser(int);
        ~LinkedList(){
            delete head;
        }
};

void LinkedList :: Display(){
    cout<<"\nLinked List : ";
    if(head == NULL){   //linked list is empty
        cout<<"EMPTY!!!!!";
        return;
    }else{
        for(Node* cur = head; cur != NULL ; cur = cur->next){     //until node reaches the last node of the LL
            cout<<cur->val<<" -> ";  //prints the Node value on the console
        }
    } 
    //cout<<"\nEnd L.Display;";
}

void LinkedList :: InserAtBeg(int v){ //Head->NewNode->Prev1stNode->... OR  Head->NewNode->NULL
    //cout<<"\nInside L.InserAtBeg;";
    Node* newNode = new Node();
    newNode->val = v;  //creates a new node with the given value
    newNode->next = head; //NewNode->Prev1stNode, Head->Prev1stNode
    head = newNode;    //Head->NewNode->Prev1stNode
    size++;
    //cout<<"\nEnd of L.InserAtBeg;";
}

void LinkedList :: InserAtEnd(int v){   //PrevEnd->NewNode->NULL    OR      Head->NewNode->NULL
    Node* newNode = new Node();
    newNode->val = v;
    newNode->next = NULL;    //NewNode->NULL
    if(head == NULL){   //List is EMPTY
        head = newNode;    //Head->NewNode->NULL
    }else{
        Node* temp = head;
        while(temp->next != NULL){   //till the last node
            temp = temp->next;
        }
        temp->next = newNode;   //adding the new node at the end
    }
    //cout<<"\nNew Node inserted successfully!";
    size++;
}

void LinkedList :: Inser(int v){
    Node* newNode = new Node();
    newNode->val = v;
    if(head == NULL){   //EMPTY
        head = newNode; //1st node inserted
        newNode->next = NULL;
    }else{
        BubbleSort();   //sorts the list in asc order
        if(head->val >= v){ //insertion at first position
            newNode->next = head;
            head = newNode;
        }else{  //insertion in asc order , list is not empty, not inserting at the first place
            Node* temp1,* temp2;
            temp1 = head->next; //temp1 points to the 2nd Node
            temp2 = head;   //temp2 points to 1st Node
            while(temp1->val <= v && temp1 != NULL ){
                temp2 = temp1;
                temp1 = temp1->next;
            }
            if(temp1 == NULL){  //reached the end of the list
                temp1 = newNode;    //adding the new node at the end
                newNode->next = NULL;   
            }else{
                temp2->next = newNode;  //inserting a node b/w temp2 and temp1
                newNode->next = temp1;
            }
        }
    }
    //cout<<"\nNew Node inserted successfully!";
    size++;
}

void Swap(Node* a, Node*b){
    int temp = b->val;
    b->val = a->val;
    a->val = temp;
}

void LinkedList :: BubbleSort(){ 
    int swapped = 0;
    Node* left; //points to the start of the list
    Node* right = NULL; //points to the end of the list
    do{
        left = head;
        swapped = 0;
        while( left->next != right ){   //defines a range
            if(left->val > left->next->val){
                Swap(left, left->next);
                swapped = 1;
            }
            left = left->next;
        }
        right = left;   //largest element is already at the end of the list no need to check that
    }while(swapped);    //if number of swaps = 0, loop stops, every two adjacent elements are in asc. order
    /*Display();*/
}

void LinkedList::Del(int delNode){
    if(head == NULL){
        cout<<"\nEmpty!";
    }else{
        Node* temp1, *temp2;
        temp1 = head;
        while(temp1 != NULL){
            if(temp1->val == delNode){
                temp2->next = temp1->next;
                delete temp1; 
                return;
            }
            temp2 = temp1;
            temp1 = temp1->next;
        }
        cout<<"\nNot found!";
    }
}

void LinkedList::DelAtBeg(){
    if(head == NULL){
        cout<<"\nEmpty!";
    }else if(head->next == NULL){
        head = NULL;
    }else{

        Node* temp;
        temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::DelAtEnd(){
    if(head == NULL){
        cout<<"\nEmpty!";
    }else if(head->next == NULL){
        head = NULL;
    }else{
        Node* temp;
        temp = head;
        while((temp->next)->next != NULL){
            temp = temp->next;
        }
        temp->next = NULL;
        delete temp;
    }
}

int main(){
    LinkedList L = LinkedList();
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
                cout<<"\t2.asc. order";
                cout<<"\t3.at the end";
                cout<<"\nEnter your choice(1-3) : ";
                cin>>k;

                    switch(k){
                        case 1: {
                            L.InserAtBeg(val);
                        }
                        break;
                        case 2: {
                            L.Inser(val);
                        }
                        break;
                        case 3: {
                            L.InserAtEnd(val);
                        }
                        break;
                        default : cout<<"\nWrong input!";
                    }
                 
            }break;

            case 2 :{
                cout<<"\nDELETION";
                cout<<"\t1.from the beginning";
                cout<<"\t2.from a specific position";
                cout<<"\t3.from the end";
                cout<<"\nEnter your choice(1-3) : ";
                cin>>k;

                    switch(k){
                        case 1: {
                            L.DelAtBeg();
                        }
                        break;
                        case 2: {
                            int pos;
                            cout<<"\nEnter the node you widh to delete : ";
                            cin>>pos;
                            L.Del(pos);
                        }
                        break;
                        case 3: {
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





















