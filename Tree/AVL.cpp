#include <iostream>
#include <cmath>

using namespace std;

//----------------------N O D E   C L A S S-----------------------

class Node{
    public:
        Node *Lchild;
        int Data;
        int Height;
        Node *Rchild;

        Node(int);

        int NodeHeight();

        int BalanceFactor();
};

//----------------------A V L    C L A S S-----------------------

class AVLtree{
    Node *root;
    int noOfNodes;

    public:
        AVLtree();

        double Height();

        Node* LLRotation(Node* p);
        Node* LRRotation(Node* p);
        Node* RRRotation(Node* p);
        Node* RLRotation(Node* p);

        void Insert(int);
        Node* Insert(Node* p, int);

        void InOrder();
        void InOrder(Node* p);
        void LevelOrder();
};

//----------------------N O D E   C L A S S   F X N S-----------------------

Node :: Node(int val){
    Data = val;
    Lchild = NULL;
    Rchild = NULL;
}

int Node :: NodeHeight(){
    int HL, HR;

    HL = (this->Lchild) ? this->Lchild->Height : 0;
    HR = (this->Rchild) ? this->Rchild->Height : 0;

    return (HL > HR) ? (HL + 1) : (HR + 1);
}

int Node :: BalanceFactor(){
    int HL, HR;

    HL = (this->Lchild) ? this->Lchild->Height : 0;
    HR = (this->Rchild) ? this->Rchild->Height : 0;

    return (HL-HR); 
}

//----------------------R  O  T  A  T  I  O  N  S-----------------------

Node* AVLtree :: LLRotation(Node* A){
    cout << "\nPerforming LL Rotation ...";

    Node* B = A->Lchild;    //B = AL
    Node* BR = B->Rchild;

    B->Rchild = A;
    A->Lchild = BR;

    //jo badale h unki height nikalenge
    //pehle bacho ki fhir parent ki
    A->Height = A->NodeHeight();
    B->Height = B->NodeHeight();

    if(root == A){
        root = B;
    }

    LevelOrder();

    return B;
}

Node* AVLtree :: LRRotation(Node* A){
    cout << "\nPerforming LR Rotation ...";

    Node* B = A->Lchild;
    Node* C = B->Rchild;

    B->Rchild = C->Lchild;
    A->Lchild = C->Rchild;

    C->Lchild = B;
    C->Rchild = A;

    B->Height = B->NodeHeight();
    A->Height = A->NodeHeight();
    C->Height = C->NodeHeight();

    if(root == A){
        root = C;
    }

    LevelOrder();
    return C;
}

Node* AVLtree :: RRRotation(Node* A){
    cout << "\nPerforming RR Rotation ...";

    Node* B = A->Rchild;
    Node* C = B->Rchild;
    Node* BL = B->Lchild;

    B->Lchild = A;
    B->Rchild = C;

    A->Rchild = BL;

    A->Height = A->NodeHeight();
    B->Height = B->NodeHeight();

    if(root == A){
        root = B;
    }

    LevelOrder();
    return B;
}

Node* AVLtree :: RLRotation(Node* A){
    cout << "\nPerforming RL Rotation ...";

    Node* B = A->Rchild;
    Node* C = B->Lchild;

    A->Rchild = C->Lchild;
    B->Lchild = C->Rchild;

    C->Lchild = A;
    C->Rchild = B;

    A->Height = A->NodeHeight();
    B->Height = B->NodeHeight();
    C->Height = C->NodeHeight();

    if(root == A){
        root = C;
    }

    LevelOrder();
    return C;
}

//----------------------A V L    C L A S S    F X N S-----------------------

AVLtree :: AVLtree(){
    root = NULL;
}

double AVLtree :: Height() {
    return log(noOfNodes);
}

void AVLtree :: Insert(int Key){
    cout << "\nInitially tree ...";
    LevelOrder();

    root = Insert(root, Key);

    cout << "\nAfter insertion ...";
    LevelOrder();
}

Node* AVLtree :: Insert(Node* p, int Key){
    noOfNodes++;

    if(p == NULL){
        Node *t = new Node(Key);
        return t;
    }

    if(Key < p->Data){
        p->Lchild = Insert(p->Lchild, Key);
    }else if(Key > p->Data){
        p->Rchild = Insert(p->Rchild, Key);
    }

    p->Height = p->NodeHeight();

    if(p->BalanceFactor() == 2  &&  p->Lchild->BalanceFactor() == 1 ){
        return LLRotation(p);
    }else if(p->BalanceFactor() == 2  &&  p->Lchild->BalanceFactor() == -1 ){
        return LRRotation(p);
    }else if(p->BalanceFactor() == -2  &&  p->Rchild->BalanceFactor() == -1 ){
        return RRRotation(p);
    }else if(p->BalanceFactor() == -2  &&  p->Rchild->BalanceFactor() == 1 ){
        return RLRotation(p);
    }

    return p;
}

//-----------------------------A V L : D I S P L A Y-----------------------------

void AVLtree :: InOrder(){
    InOrder(root);
}

void AVLtree :: InOrder(Node* p){
    if(p){
        InOrder(p->Lchild);
        cout<<p->Data<<"  ";
        InOrder(p->Rchild);
    }
}

void AVLtree :: LevelOrder(){
    if(root) {
        cout << endl;

        queue<Node *> q;
        q.push(root);    

        while (!q.empty()) {
            int levelSize = q.size();  

            for (int i = 0; i < levelSize; ++i) {
                Node* node = q.front();  
                cout << node->Data << "   ";  
                q.pop();  
                
                if (node->Lchild != nullptr)
                    q.push(node->Lchild);
                
                if (node->Rchild != nullptr)
                    q.push(node->Rchild);
            }
            cout << endl;  
        }
    }
}

//-----------------------------M A I N-----------------------------

int main(){
    AVLtree A;

    char ch = 'Y';
    while(ch=='Y'||ch=='y') {
        int x = -1;
        cout << "\nInsert node value : ";
        cin >> x;        
        A.Insert(x);

        cout << "\nDo you want to continue adding nodes ? (y/n) ";
        cin.sync();
        cin >> ch;
    }

    return 0;
}