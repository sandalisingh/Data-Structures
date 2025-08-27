#include <iostream>
#include <algorithm>
using namespace std;

struct AVLNode {
    int val;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int v) : val(v), left(nullptr), right(nullptr), height(1) {}
};

// Gets the height of a node, handling nullptr cases
int getHeight(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int getBalance(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    //update heights bottom up
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    //update heights bottom up
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}


AVLNode* insert(AVLNode* node, int key) {
    // 1. Standard BST insertion
    if (node == nullptr) {
        return new AVLNode(key);
    }
    if (key < node->val) {
        node->left = insert(node->left, key);
    } 
    else if (key > node->val) {
        node->right = insert(node->right, key);
    } 
    else {
        return node; // No duplicate keys
    }

    // 2. Update height of the current node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 3. Get the balance factor to check for imbalance
    int balance = getBalance(node);

    // 4. If unbalanced, perform rotations
    // Left Left Case (LL) - Left child's left subtree	
    if (balance > 1 && key < node->left->val) {
        return rightRotate(node);
    }
    // Right Right Case (RR) - Right child's right subtree	
    if (balance < -1 && key > node->right->val) {
        return leftRotate(node);
    }
    // Left Right Case (LR) - Left child's right subtree
    if (balance > 1 && key > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case (RR) - Right child's left subtree	
    if (balance < -1 && key < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


AVLNode* buildAVLTree() {
    AVLNode* root = nullptr;
    cout << "Enter data for the AVL tree (enter -1 to stop): ";
    int data;
    cin >> data;
    while (data != -1) {
        root = insert(root, data);
        cout << "Enter next data (enter -1 to stop): ";
        cin >> data;
    }
    return root;
}

void inorderTraversal(AVLNode* root) {
    if (!root) {
        return;
    }
    inorderTraversal(root->left); 
    cout << root->val << " ";
    inorderTraversal(root->right);
}

void preorderTraversal(AVLNode* root) {
    if (!root) {
        return;
    }
    cout << root->val << " ";   
    preorderTraversal(root->left); 
    preorderTraversal(root->right); 
}

void postorderTraversal(AVLNode* root) {
    if (!root) { 
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->val << " ";  
}


void destroy(AVLNode* node) {
    if (!node) { 
        return;
    }
    destroy(node->left); 
    destroy(node->right); 
    delete node;
}


int main() {
    AVLNode* root = nullptr; 

    root = buildAVLTree();

    cout << "\nIn-order Traversal: ";
    inorderTraversal(root);
    cout << endl;

    cout << "Pre-order Traversal: ";
    preorderTraversal(root);
    cout << endl;

    cout << "Post-order Traversal: ";
    postorderTraversal(root);
    cout << endl;

    destroy(root);
    return 0; 
}