//PRACTICE

#include <iostream>

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

    public:
        AVLtree();

        Node* LLRotation(Node* p);
        Node* LRRotation(Node* p);
        Node* RRRotation(Node* p);
        Node* RLRotation(Node* p);

        void RInsert(int);
        Node* RInsert(Node* p, int);

        void InOrder();
        void InOrder(Node* p);
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

    return B;
}

Node* AVLtree :: LRRotation(Node* A){
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

    return C;
}

Node* AVLtree :: RRRotation(Node* A){
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

    return B;
}

Node* AVLtree :: RLRotation(Node* A){
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

    return C;
}

//----------------------A V L    C L A S S    F X N S-----------------------

AVLtree :: AVLtree(){
    root = NULL;
}

void AVLtree :: RInsert(int Key){
    root = RInsert(root, Key);
}

Node* AVLtree :: RInsert(Node* p, int Key){
    if(p == NULL){
        Node *t = new Node(Key);
        return t;
    }

    if(Key < p->Data){
        p->Lchild = RInsert(p->Lchild, Key);
    }else if(Key > p->Data){
        p->Rchild = RInsert(p->Rchild, Key);
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

//-----------------------------M A I N-----------------------------

int main(){
    AVLtree A;
    A.RInsert(20);
    A.RInsert(10);
    A.RInsert(30);

    A.RInsert(5);
    A.RInsert(15);
    A.RInsert(25);
    A.RInsert(40);

    A.RInsert(4);
    A.RInsert(28);
    A.RInsert(50);

    A.InOrder();

    return 0;
}