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

double AVLtree :: Height() {
    return log(noOfNodes);
}

void AVLtree :: Insert(int Key){
    cout << "Initially tree " << endl;
    LevelOrder();

    root = Insert(root, Key);

    cout << "After insertion " << endl;
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
        queue<Node *> q;
        q.push(root);    

        int totalHeight = Height();
        int level = 0;

        while (!q.empty()) {
            int levelSize = q.size();  
            for (int i = 0; i < ((totalHeight-level)/2); ++i) {
                cout << "   "; 
            }

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
            level++;
        }
    }
}

//-----------------------------M A I N-----------------------------

int main(){
    AVLtree A;

    // A.Insert(20);
    // A.Insert(10);
    // A.Insert(30);

    // A.Insert(5);
    // A.Insert(15);
    // A.Insert(25);
    // A.Insert(40);

    // A.Insert(4);
    // A.Insert(28);
    // A.Insert(50);

    char ch = 'Y';
    while(ch=='Y'||ch=='y') {
        int x = -1;
        cout << "Insert node value : ";
        cin >> x;
        fflush(stdin);
        
        A.Insert(x);

        cout << "Do you want to continue adding nodes ? (y/n) ";
        ch = getchar();
    }

    return 0;
}