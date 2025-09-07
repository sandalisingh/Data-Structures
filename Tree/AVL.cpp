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

//----------------------N O D E   C L A S S   F X N S-----------------------

Node :: Node(int val){
    Data = val;
    Lchild = NULL;
    Rchild = NULL;
}

int Node :: NodeHeight(){
    int HL, HR;

    HL = (this->Lchild) ? this->Lchild->NodeHeight() : 0;
    HR = (this->Rchild) ? this->Rchild->NodeHeight() : 0;

    Height = (HL > HR) ? (HL + 1) : (HR + 1);

    return Height;
}

int Node :: BalanceFactor(){
    int HL, HR;

    HL = (this->Lchild) ? this->Lchild->NodeHeight() : 0;
    HR = (this->Rchild) ? this->Rchild->NodeHeight() : 0;

    return (HL-HR); 
}

//----------------------A V L    C L A S S-----------------------

class AVLtree{
    Node *root;

    public:
        AVLtree();

        double Height();

        Node* LLRotation(Node* p);
        Node* LRRotation(Node* p);
        Node* RRRotation(Node* p);
        Node* RLRotation(Node* p);

        void Insert(int);
        Node* Insert(Node* p, int);
        void Delete(int);
        Node* Delete(Node* node, int Key);

        void InOrder();
        void InOrder(Node* p);
        void PreOrder();
        void PreOrder(Node* p);
        void PostOrder();
        void PostOrder(Node* p);
        void LevelOrder();

        vector<vector<string>> toMatrix();
        void Display();

        void deleteNode(Node* node);
        ~ AVLtree();
};

//----------------------R  O  T  A  T  I  O  N  S-----------------------

Node* AVLtree :: RRRotation(Node* A){
    cout << "\nPerforming RR Rotation ...\n";

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

    Display();
    return B;
}

Node* AVLtree :: LRRotation(Node* A){
    cout << "\nPerforming LR Rotation ...\n";

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

    Display();
    return C;
}

Node* AVLtree :: LLRotation(Node* A){
    cout << "\nPerforming LL Rotation ...\n";

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

    Display();
    return B;
}

Node* AVLtree :: RLRotation(Node* A){
    cout << "\nPerforming RL Rotation ...\n";

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

    Display();
    return C;
}

//----------------------A V L    O P E R A T I O N S-----------------------

AVLtree :: AVLtree(){
    root = NULL;
}

double AVLtree :: Height() {
    if (root==NULL) {
        return 0;
    }
    return root->NodeHeight();
}

void AVLtree :: Insert(int Key){
    cout << "\nInitially tree ...\n";
    Display();

    root = Insert(root, Key);

    cout << "\nAfter insertion ...\n";
    Display();
}

Node* AVLtree :: Insert(Node* p, int Key){
    if(p == NULL){
        Node *t = new Node(Key);
        return t;
    }

    if(Key < p->Data){
        p->Lchild = Insert(p->Lchild, Key);
    }else if(Key > p->Data){
        p->Rchild = Insert(p->Rchild, Key);
    }else{
        return p;
    }

    p->Height = p->NodeHeight();

    cout << "\nBalance factor of Node:" << p->Data << " = " << p->BalanceFactor() << endl;

    if(p->BalanceFactor() == 2  &&  p->Lchild->BalanceFactor() >= 0 ){
        return RRRotation(p);
    }else if(p->BalanceFactor() == 2  &&  p->Lchild->BalanceFactor() == -1 ){
        return LRRotation(p);
    }else if(p->BalanceFactor() == -2  &&  p->Rchild->BalanceFactor() <= 0 ){
        return LLRotation(p);
    }else if(p->BalanceFactor() == -2  &&  p->Rchild->BalanceFactor() == 1 ){
        return RLRotation(p);
    }

    return p;
}

void AVLtree :: Delete(int Key){
    cout << "\nInitially tree ...\n";
    Display();

    root = Delete(root, Key);

    cout << "\nAfter deletion ...\n";
    Display();
}

Node* AVLtree :: Delete(Node* p, int Key){
    if(p) {
        if (Key < p->Data) {
            p->Lchild = Delete(p->Lchild, Key);
        } 
        else if (Key > p->Data) {
            p->Rchild = Delete(p->Rchild, Key);
        } 
        else { // key found
            // Node with only one child or no child
            if ((p->Lchild == nullptr) || (p->Rchild == nullptr)) {
                Node* temp = p->Lchild ? p->Lchild: p->Rchild;

                // No child case
                if (temp == nullptr) {
                    cout << "\nDeleting Node:" << p->Data << "..." << endl;
                    temp = p;
                    p = nullptr; // Node is now null, effectively deleted
                } 
                // One child case
                else { 
                    *p = *temp; // Copy the contents of the non-empty child
                }
                delete temp; // Free the memory of the original node or its child
            } 
            else {
                // Node with two children: Get the in-order successor (smallest in the right subtree)
                Node* successor = p->Rchild; 
                while (successor->Lchild != nullptr) { 
                    successor = successor->Lchild;
                }

                cout << "\nReplacing Node:" << Key << " with Node:" << successor->Data << endl;

                // Copy the in-order successor's data to this node
                p->Data = successor->Data;

                // Delete the in-order successor from the right subtree
                p->Rchild = Delete(p->Rchild, successor->Data);

                cout << "\nAfter deleting node...\n";
                Display();
            }
        }

        if(!p)  return nullptr;

        p->Height = p->NodeHeight();

        cout << "\nBalance factor of Node:" << p->Data << " = " << p->BalanceFactor() << endl;

        if(p->BalanceFactor() == 2  &&  p->Lchild->BalanceFactor() >= 0 ){
            return RRRotation(p);
        }else if(p->BalanceFactor() == 2  &&  p->Lchild->BalanceFactor() == -1 ){
            return LRRotation(p);
        }else if(p->BalanceFactor() == -2  &&  p->Rchild->BalanceFactor() <= 0 ){
            return LLRotation(p);
        }else if(p->BalanceFactor() == -2  &&  p->Rchild->BalanceFactor() == 1 ){
            return RLRotation(p);
        }

        return p;
    }

    return p;
}

void AVLtree :: deleteNode(Node* node){
    if (!node) {
        return;
    }
    deleteNode(node->Lchild);
    deleteNode(node->Rchild);
    delete node;
}

AVLtree :: ~ AVLtree(){
    deleteNode(root);
}

//-----------------------------A V L : T R A V E R S A L S-----------------------------

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

void AVLtree :: PreOrder(){
    PreOrder(root);
}

void AVLtree :: PreOrder(Node* p){
    if(p){
        cout<<p->Data<<"  ";
        PreOrder(p->Lchild);
        PreOrder(p->Rchild);
    }
}

void AVLtree :: PostOrder(){
    PostOrder(root);
}

void AVLtree :: PostOrder(Node* p){
    if(p){
        PostOrder(p->Lchild);
        PostOrder(p->Rchild);
        cout<<p->Data<<"  ";
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

//-----------------------------A V L : D I S P L A Y-----------------------------

void inorder(Node *root, int row, int col, int height,
             vector<vector<string>> &matrix) {
    if (!root) {
        return;
    }

    int offset = pow(2, height - row - 1);

    // traverse left subtree
    if (root->Lchild) {
        inorder(root->Lchild, row + 1, col - offset, height, matrix);
    }

    matrix[row][col] = to_string(root->Data);

    // traverse right subtree
    if (root->Rchild) {
        inorder(root->Rchild, row + 1, col + offset, height, matrix);
    }
}

vector<vector<string>> AVLtree :: toMatrix() {

    int height = (root) ? root->NodeHeight() : 0;

    int rows = height + 1;
    int cols = pow(2, height + 1) - 1;

    vector<vector<string>> matrix(rows, vector<string>(cols+2, ""));

    inorder(root, 0, (cols - 1) / 2, height, matrix);
    return matrix;
}

void print2DArray(vector<vector<string>> &arr) {
    for (auto &row : arr) {
        for (auto &cell : row) {
            if (cell.empty()) {
                cout << " ";
            }
            else {
                cout << cell;
            }
        }
        cout << endl;
    }
}

void AVLtree :: Display() {
    vector<vector<string>> matrix = toMatrix();
    print2DArray(matrix);
}


//-----------------------------M A I N-----------------------------

int main(){
    AVLtree A;

    int option = -1;
    while(option!=9) {
        cout << "\n\n----------------------------------------------------";
        cout << "\n\n\t\tAVL TREE : MENU";
        cout << "\n1. Display tree";
        cout << "\n2. Height of tree";
        cout << "\n3. Insert node";
        cout << "\n4. Delete node";
        cout << "\n5. Display level-order traversal";
        cout << "\n6. Display pre-order traversal";
        cout << "\n7. Display post-order traversal";
        cout << "\n8. Display in-order traversal";
        cout << "\n9. Exit";
        cout << "\n--> Select any one of the above options (1-9) : ";
        cin.sync();
        cin >> option;

        switch(option) {
            case 1: {
                cout << "\nTree : \n";
                A.Display();
            } break;
            case 2: {
                cout << "\nHeight of tree = " << A.Height();
            } break;
            case 3: {
                int x = -1;
                cout << "\nInsert node value : ";
                cin >> x;        
                A.Insert(x);
            } break;
            case 4: {
                int x = -1;
                cout << "\nDelete node value : ";
                cin >> x;        
                A.Delete(x);
            } break;
            case 5: {
                cout << "\nLevel-order traversal : ";
                A.LevelOrder();
            } break;
            case 6: {
                cout << "\nPre-order traversal : ";
                A.PreOrder();
            } break;
            case 7: {
                cout << "\nPost-order traversal : ";
                A.PostOrder();
            } break;
            case 8: {
                cout << "\nIn-order traversal : ";
                A.InOrder();
            } break;
            case 9: {
                return 0;
            } break;
            default: cout << "\nWrong option selected !!";
        }
    }

    return 0;
}