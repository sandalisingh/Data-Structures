//ERROR in Postorder_Iteration()

#include <iostream>
#include "../Queue_LLImplementation.h"
#include "../Stack.h"
#include <vector>
#include <queue>

using namespace std;

#define TYPE char
#define NONE '-'

//-----------------------T R E E    C L A S S-------------------------

class Tree{
    public:
        Node<TYPE> *root;
        Tree();
        void CreateTree();

        //--------------PRE ORDER------------

        void PreOrder_Recursion();
        void PreOrder_Recursion(Node<TYPE> *p);

        void PreOrder_Iteration();
        void PreOrder_Iteration(Node<TYPE> *t);

        //--------------POST ORDER------------

        void PostOrder_Recursion();
        void PostOrder_Recursion(Node<TYPE> *p);

        // void PostOrder_Iteration();
        // void PostOrder_Iteration(Node<TYPE> *p);

        //--------------IN ORDER------------

        void InOrder_Recursion();
        void InOrder_Recursion(Node<TYPE> *p);

        void InOrder_Iteration();
        void InOrder_Iteration(Node<TYPE> *p);

        //--------------LEVEL ORDER------------

        void LevelOrder();
        void LevelOrder(Node<TYPE> *root);
        vector<vector<int> > levelOrder(Node<TYPE> *root);

        //--------------H E I G H T------------

        int Height();
        int Height(Node<TYPE> *root);

        //--------------C O U N T------------

        int count();
        int count(Node<TYPE> *p);

        int count_Nodes_deg0();
        int count_Nodes_deg0(Node<TYPE> *p);

        int count_Nodes_deg2();
        int count_Nodes_deg2(Node<TYPE> *p);

        int count_Nodes_deg_1or2();
        int count_Nodes_deg_1or2(Node<TYPE> *p);

        int count_Nodes_deg1();
        int count_Nodes_deg1(Node<TYPE> *p);

        //--------------S U M  O F   E L E M E N T S------------

        int SumOfAllElements();
        int SumOfAllElements(Node<TYPE> *p);

        int Fun(Node<TYPE> *p);
};

//-----------------------T R E E    F X N S-------------------------

Tree :: Tree(){
    root = NULL;
}

void Tree :: CreateTree(){
    Node<TYPE> *p, *t;
    TYPE x;
    Queue<TYPE> Q(20);

    //INSERTING ROOT NODE

    cout<<"\nRoot : ";
    cin>>x;

    root = new Node<TYPE>;
    root->data = x;
    root->Lchild = NULL;
    root->Rchild = NULL;

    Q.Enqueue(root);

    while(!Q.isEmpty()){
        p = Q.DequeueNode();

        //INSERTING LEFT CHILD

        cout<<"\nLeft Child of "<<p->data<<" : ";
        cin>>x;

        if(x != NONE){
            t = new Node<TYPE>;
            t->data = x;
            t->Lchild = NULL;
            t->Rchild = NULL;

            p->Lchild = t;

            Q.Enqueue(t);
        }

        //INSERTING RIGHT CHILD

        cout<<"\nRight Child of "<<p->data<<" : ";
        cin>>x;

        if(x != NONE){
            t = new Node<TYPE>;
            t->data = x;
            t->Lchild = NULL;
            t->Rchild = NULL;

            p->Rchild = t;

            Q.Enqueue(t);
        }
    }
}

//----------------------PRE ORDER--------------------------

void Tree :: PreOrder_Recursion(){
    PreOrder_Recursion(root);
}

void Tree :: PreOrder_Recursion(Node<TYPE> *p){
    if(p){
        cout<<" "<<p->data;
        PreOrder_Recursion(p->Lchild);
        PreOrder_Recursion(p->Rchild);
    }
}

void Tree :: PreOrder_Iteration(){
    PreOrder_Iteration(root);
}

void Tree :: PreOrder_Iteration(Node<TYPE> *t){
    Stack<Node<TYPE>*> St;

    while( t || !St.isEmpty()){
        if(t){
            cout<<t->data<<" ";

            St.push(t);

            t = t->Lchild;
        }else{
            t = St.pop();

            t = t->Rchild;
        }
    }
}

//----------------------POST ORDER--------------------------

void Tree :: PostOrder_Recursion(){
    PostOrder_Recursion(root);
}

void Tree :: PostOrder_Recursion(Node<TYPE> *p){
    if(p){
        PostOrder_Recursion(p->Lchild);
        PostOrder_Recursion(p->Rchild);
        cout<<" "<<p->data;
    }
}

// void Tree :: PostOrder_Iteration(){
//     PostOrder_Iteration(root);
// }

// void Tree :: PostOrder_Iteration(Node<TYPE> *t){    //SEGMENTATION FAULT
//     Stack<long int> St;
//     long int temp;

//     while( t!=NULL || !St.isEmpty()){
//         if(t != NULL){
//             St.push((long int)t);

//             t = t->Lchild;
//         }else{  //t == NULL
//             temp = St.pop();

//             if(temp > 0){
//                 St.push(-temp);

//                 t = ((Node<TYPE>*)temp)->Rchild;
//             }else{
//                 cout<<" "<<((Node<TYPE>*)temp)->data;

//                 t = NULL;
//             }
//         }
//     }
// }

//-----------------------IN ORDER--------------------------

//RECURSION

void Tree :: InOrder_Recursion(){
    InOrder_Recursion(root);
}

void Tree :: InOrder_Recursion(Node<TYPE> *p){
    if(p){
        InOrder_Recursion(p->Lchild);
        cout<<" "<<p->data;
        InOrder_Recursion(p->Rchild);
    }
}

//ITERATION

void Tree :: InOrder_Iteration(){
    InOrder_Iteration(root);
}

void Tree :: InOrder_Iteration(Node<TYPE> *t){
    Stack<Node<TYPE>*> St;

    while( t || !St.isEmpty()){
        if(t){
            St.push(t);

            t = t->Lchild;
        }else{
            t = St.pop();

            cout<<t->data<<" ";
            
            t = t->Rchild;
        }
    }
}

//-----------------------LEVEL ORDER--------------------------

void Tree :: LevelOrder(){
    // LevelOrder(root);
    levelOrder(root);
}

void Tree :: LevelOrder(Node<TYPE> *root){
    Queue<TYPE> Q(20);

    cout<<root->data<<" ";

    Q.Enqueue(root);

    while(!Q.isEmpty()){
        root = Q.DequeueNode();

        if(root->Lchild){
            cout<<root->Lchild->data<<" ";
            Q.Enqueue(root->Lchild);
        }

        if(root->Rchild){
            cout<<root->Rchild->data<<" ";
            Q.Enqueue(root->Rchild);
        }
    }
}

void DisplayVectorMatrix(vector<vector<int> > M) {
    cout<<"\nVECTOR MATRIX\n";
    for(auto m : M) {
        for(auto i : m) {
            cout<<i<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

vector<vector<int> > Tree :: levelOrder(Node<TYPE> *root) {
    vector<vector<int> > ANS;
    
    if(!root) {
        return ANS;
    }
    
    queue<Node<TYPE> *> Q;
    
    
    vector<int> Level;
    
    int LevelNo = 1, Count = 0;
        
    Q.push(root);
    
    Level.push_back(root->data);
    ANS.push_back(Level);
    Level.pop_back();
    
    if(root->Lchild == nullptr && root->Rchild == nullptr) {
        return ANS;
    }
    
    while(Q.size() != 0) {
        root = Q.back();
        Q.pop();
        
        Count++;
        
        if(root->Lchild) {
            Level.push_back(root->Lchild->data);
            Q.push(root->Lchild);
        }
        
        if(root->Rchild) {
            Level.push_back(root->Rchild->data);
            Q.push(root->Rchild);
        }
        
        if(Count == LevelNo) {
            LevelNo++;
            Count = 0;
            ANS.push_back(Level);
            Level.clear();
        }
    }

    DisplayVectorMatrix(ANS);
    
    return ANS;
}

//-----------------------H E I G H T--------------------------

int Tree :: Height(){
    return Height(root);
}

int Tree :: Height(Node<TYPE> *root){
    int x = 0, y = 0;
    
    if(root == NULL){
        return 0;
    }

    x = Height(root->Lchild);
    y = Height(root->Rchild);

    if(x > y){
        return (x + 1);
    }else{
        return (y + 1);
    }
}

//-----------------------C O U N T   N O D E S--------------------------

int Tree :: count(){
    return count(root);
}

int Tree :: count(Node<TYPE> *p){
    if(p){
        return (count(p->Lchild) + count(p->Rchild) + 1);
    }
    return 0;
}

int Tree :: count_Nodes_deg0(){
    return count_Nodes_deg0(root);
}

int Tree :: count_Nodes_deg0(Node<TYPE> *p){
    int x, y;

    if(p){
        x = count_Nodes_deg0(p->Lchild);
        y = count_Nodes_deg0(p->Rchild);

        if(!p->Lchild && !p->Rchild){
            return (x + y + 1);
        }else{
            return (x + y);
        }       
    }

    return 0;
}

int Tree :: count_Nodes_deg2(){
    return count_Nodes_deg2(root);
}

int Tree :: count_Nodes_deg2(Node<TYPE> *p){     
    int x, y;

    if(p){
        x = count_Nodes_deg2(p->Lchild);
        y = count_Nodes_deg2(p->Rchild);

        if(p->Lchild && p->Rchild){
            return (x + y + 1);
        }else{
            return (x + y);
        }
    }

    return 0;
}

int Tree :: count_Nodes_deg_1or2(){
    return count_Nodes_deg_1or2(root);
}

int Tree :: count_Nodes_deg_1or2(Node<TYPE> *p){     
    int x, y;

    if(p){
        x = count_Nodes_deg_1or2(p->Lchild);
        y = count_Nodes_deg_1or2(p->Rchild);

        if(p->Lchild || p->Rchild){
            return (x + y + 1);
        }else{
            return (x + y);
        }
    }

    return 0;
}

int Tree :: count_Nodes_deg1(){
    return count_Nodes_deg1(root);
}

int Tree :: count_Nodes_deg1(Node<TYPE> *p){     
    int x, y;

    if(p){
        x = count_Nodes_deg1(p->Lchild);
        y = count_Nodes_deg1(p->Rchild);

        if(
            (p->Lchild && !p->Rchild) 
            || (!p->Lchild && p->Rchild)
        ){
            return (x + y + 1);
        }else{
            return (x + y);
        }
    }

    return 0;
}



//-----------------------S U M  O F   E L E M E N T S--------------------------

int Tree :: SumOfAllElements(){
    return SumOfAllElements(root);
}

int Tree :: SumOfAllElements(Node<TYPE> *p){
    int x, y;

    if(p){
        x = SumOfAllElements(p->Lchild);
        y = SumOfAllElements(p->Rchild);

        return (x + y + p->data);
    }

    return 0;
}

int Tree :: Fun(Node<TYPE> *p){
    int x, y;

    if(p){
        x = Fun(p->Lchild);
        y = Fun(p->Rchild);

        return (x + y + p->data);
    }

    return 0;
}

//-----------------------M A I N--------------------------

int main() {
    Tree T;

    cout<<"\n\nCREATE TREE\n";
    T.CreateTree();

    // // //-------------PRE ORDER--------------------------
    cout<<"\n\nPREOREDR RECURSION\n";
    T.PreOrder_Recursion();

    cout<<"\n\nPREOREDR ITERATION\n";
    T.PreOrder_Iteration();

    //-------------IN ORDER--------------------------
    cout<<"\n\nTRAVERSAL\n";
    cout<<"\n\nINOREDR RECURSION\n";
    T.InOrder_Recursion();

    cout<<"\n\nPREOREDR RECURSION\n";
    T.PreOrder_Recursion();

    cout<<"\n\nPOSTOREDR RECURSION\n";
    T.PostOrder_Recursion();

    cout<<"\n\nINOREDR ITERATION\n";
    T.InOrder_Iteration();
    
    // //-------------POST ORDER--------------------------
    cout<<"\n\nPOSTOREDR RECURSION\n";
    T.PostOrder_Recursion();

    // // cout<<"\n\nPOSTOREDR ITERATION\n";
    // // T.PostOrder_Iteration();

    cout<<"\n\nLEVEL OREDR\n";
    T.LevelOrder();

    int H = T.Height();
    cout<<"\n\nHEIGHT = "<<H;

    // int count = T.countNode();
    // cout<<"\n\nNumber of Nodes = "<<count;

    int count = T.count();
    cout<<"\n\nNumber of Nodes = "<<count;

    // count = T.CountLeafNodes();
    // cout<<"\n\nNumber of Nodes with 0 children (LEAF NODES) = "<<count;

    // count = T.CountInternalNodes();
    // cout<<"\n\nNumber of Nodes with 1/2 children (NON LEAF NODES) = "<<count;

    count = T.count_Nodes_deg2();
    cout<<"\n\nNumber of Nodes with 2 children = "<<count;
 
    int Sum = T.SumOfAllElements();
    cout<<"\n\nSUM = "<<Sum<<endl;

    return 0;
}
