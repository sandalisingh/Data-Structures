/*
    Linked List
    Insertion at FRONT, END & SPECIFIC LOCATION (first dort it)
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
        if(head->val >= v){
            newNode->next = head;
            head = newNode;
        }
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

int main(){
    LinkedList L = LinkedList();
    char ch = 'y';
    do{
        int val;
        cout<<"\nEnter the element you wish to insert:\t";
        cin>>val;

        int k;
        cout<<"\nM E N U";
        cout<<"\n1.Insertion At The Beginning";
        cout<<"\n2.Insertion (asc. order)";
        cout<<"\n3.Insertion At The End";
        cout<<"\nEnter your choice(1-3) : ";
        cin>>k;

        switch(k){
            case 1: {
                L.InserAtBeg(val);
                L.Display();
            }
            break;
            case 2: {
                L.Inser(val);
                L.Display();
            }
            break;
            case 3: {
                L.InserAtEnd(val);
                L.Display();
            }
            break;
            default: cout<<"\nWRONG CHOICE!";
        }

        cout<<"\nDo you wish to continue?(y/n)\t";
        cin>>ch;
    }while(ch == 'y' || ch == 'Y');
    
    return 0;
}





















