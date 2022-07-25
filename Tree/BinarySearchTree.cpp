//Practice

#include <iostream>
#include "../Stack.h"
using namespace std;

//--------------------------N O D E-----------------------------------

class Node{
    public:
        Node* Lchild;
        int data;
        Node* Rchild;

        Node(int);
};

Node :: Node(int val){
    data = val;
    Lchild = NULL;
    Rchild = NULL;
}

//--------------------------B S T    C L A S S-----------------------------------

class BST{
    Node* root;

    public:
        BST();

        //------------C R E A T E------------------------

        void Create_Tree_From_PreOrder(int pre[], int n);

        //------------I N  O R D E R------------------------

        void InOrder();
        void InOrder(Node* p);

        //------------S E A R C H------------------------

        Node* Recursive_Search(Node* t, int Key);

        Node* Iterative_Search(int Key);
        Node* Iterative_Search(Node* t, int Key);

        //------------I N S E R T------------------------

        void Insert(Node* t, int Key);
        Node* Insert_Recursive(Node *p, int Key);

        void Insert(int Key);
        void Insert_Recursive(int Key);

        //------------H E I G H T------------------------

        int Height(Node *p);
        int Height();

        //------------D E L E T I O N------------------------
        Node* InPre(Node *p);
        Node* InSucc(Node *p);

        Node* Delete(int Key);
        Node* Delete(Node *p, int Key);
};

BST :: BST(){
    root = NULL;
}

//--------------------------------I N   O R D E R--------------------------------------

void BST :: InOrder(){
    InOrder(root);
}

void BST :: InOrder(Node* p){
    if(p){
        InOrder(p->Lchild);
        cout<<p->data<<"  ";
        InOrder(p->Rchild);
    }
}

//--------------------------------S E A R C H--------------------------------------

Node* BST :: Recursive_Search(Node* t, int Key){   //TAIL RECUSION
    if(t == NULL){
        return NULL;
    }else if(Key == t->data){
        return t;
    }else if(Key < t->data){
        return Recursive_Search(t->Lchild, Key);
    }else{
        return Recursive_Search(t->Rchild, Key);
    }
}

Node* BST :: Iterative_Search(int Key){
    return Iterative_Search(root, Key);
}

Node* BST :: Iterative_Search(Node*t, int Key){    //if a tail recusion is converted into loop, DONT require STACK
    while(t != NULL){
        if(Key == t->data){
            return t;
        }else if(Key < t->data){
            t = t->Lchild;
        }else{
            t = t->Rchild;
        }
    }
    return NULL;
}

//--------------------------I N S E R T I O N-----------------------------------

void BST :: Insert(int Key){
    Insert(root, Key);
}

void BST :: Insert(Node* t, int Key){
    Node *r = NULL; 
    
    Node *p = new Node(Key);

    if(t == NULL){
        t = p;
        return;
    }

    while(t != NULL){
        r = t;

        if(Key == t->data){
            return;
        }else if(Key < t->data){
            t = t->Lchild;
        }else{
            t = t->Rchild;
        }
    }

    if(p->data < r->data){
        r->Lchild = p;
    }else{
        r->Rchild = p;
    }
}

void BST :: Insert_Recursive(int Key){
    root = Insert_Recursive(root, Key);
}

Node* BST :: Insert_Recursive(Node* p, int Key){
    
    if(p == NULL){
        Node *t  = new Node(Key);
        return t;
    }

    if(Key < p->data){
        p->Lchild = Insert_Recursive(p->Lchild, Key);
    }else if(Key > p->data){
        p->Rchild = Insert_Recursive(p->Rchild, Key);
    }

    return p;
}

//--------------------------H E I G H T-----------------------------------

int BST :: Height(Node *p){
    int x, y;

    if(p == NULL){
        return 0;
    }

    x = Height(p->Lchild);
    y = Height(p->Rchild);

    return (x>y ? x+1 : y+1);
}

int BST :: Height(){
    return Height(root);
}

//--------------------------D E L E T I O N-----------------------------------

Node* BST :: InPre(Node *p){
    while(p && p->Rchild != NULL){
        p = p->Rchild;
    }

    return p;
}

Node* BST :: InSucc(Node *p){
    while(p && p->Lchild != NULL){
        p = p->Lchild;
    }

    return p;
}

Node* BST :: Delete(int Key){
    return Delete(root, Key);
}

Node* BST :: Delete(Node *p, int Key){
    Node *q;

    if(p == NULL){
        return NULL;
    }

    if(p->Lchild == NULL && p->Rchild == NULL){
        if(p == root){
            root = NULL;
        }
        delete p;
        return NULL;
    }

    if(Key < p->data){
        p->Lchild = Delete(p->Lchild, Key);
    }else if(Key > p->data){
        p->Rchild = Delete(p->Rchild, Key);
    }else{
        if(Height(p->Lchild) > Height(p->Rchild)){
            q  = InPre(p->Lchild);
            p->data = q->data;
            p->Lchild = Delete(p->Lchild, q->data);
        }else{
            q = InSucc(p->Rchild);
            p->data = q->data;
            p->Rchild = Delete(p->Rchild, q->data);
        }
    }

    return p;
}

//--------------------------C R E A T E-----------------------------------

void BST :: Create_Tree_From_PreOrder(int pre[], int n){
    Stack<Node*> St;
    Node *t, *p;
    int i = 0;

    root = new Node(pre[i++]);

    p = root;

    while(i < n){
        if(pre[i] < p->data){
            t = new Node(pre[i++]);

            p->Lchild = t;

            St.push(p);

            p = t;
        }else{
            Node* top = St.peek();
            if(pre[i] > p->data  &&  pre[i] < top->data){
                t = new Node(pre[i++]);

                p->Rchild = t;

                p= t;
            }else{
                p = St.pop();
            }
        }
    }
}

//--------------------------M A I N-----------------------------------

int main(){
    BST T;

    T.Insert_Recursive(10);
    T.Insert_Recursive(5);
    T.Insert_Recursive(20);
    T.Insert_Recursive(8);
    T.Insert_Recursive(30);
    T.Insert_Recursive(300);
    T.Insert_Recursive(3);

    T.InOrder();    //asc order

    Node* temp;
    temp = T.Iterative_Search(20);

    if(temp != NULL){
        cout<<"\nElement "<<temp->data<<" is found!\n";
    }else{
        cout<<"\nNot found!\n";
    }

    T.Delete(5);
    cout<<"\n5 deleted\n";
    T.InOrder();

    T.Delete(30);
    cout<<"\n30 deleted\n";
    T.InOrder();


    return 0;
}
