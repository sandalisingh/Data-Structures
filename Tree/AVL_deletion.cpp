#include <iostream>
#include <algorithm> 
#include <vector> 
#include <queue> 
using namespace std;

struct AVLNode {
    int val;
    AVLNode* left;
    AVLNode* right;
    int height; 

    AVLNode(int v) : val(v), left(nullptr), right(nullptr), height(1) {}
};


int getHeight(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// Calculates the balance factor of a node (height of left subtree - height of right subtree).
// A positive balance means left-heavy, negative means right-heavy.
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

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}



// Inserts a key into the AVL tree and returns the new root of the subtree.
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
        return node;  // No duplicate keys
    }

    // 2. Update height of the current node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 3. Get the balance factor to check for imbalance
    int balance = getBalance(node);

    // 4. If unbalanced, perform rotations
    // Left Left Case (LL)
    if (balance > 1 && key < node->left->val) {
        return rightRotate(node);
    }
    // Right Right Case (RR)
    if (balance < -1 && key > node->right->val) {
        return leftRotate(node);
    }
    // Left Right Case (LR)
    if (balance > 1 && key > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case (RL)
    if (balance < -1 && key < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Return the (potentially new) root of this subtree
}



AVLNode* deleteNode(AVLNode* root, int key) {
    // 1. Standard BST deletion
    if (root == nullptr) {
        return root; // Key not found
    }

    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    } 
    else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    } 
    else { // key is same as root->val, this is the node to be deleted
        // Node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            AVLNode* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr; // Node is now null, effectively deleted
            } 
            // One child case
            else { 
                *root = *temp; // Copy the contents of the non-empty child
            }
            delete temp; // Free the memory of the original node or its child
        } 
        else {
            // Node with two children: Get the in-order successor (smallest in the right subtree)
            AVLNode* successor = root->right; 
            while (successor->left != nullptr) { 
                successor = successor->left;
            }

            // Copy the in-order successor's data to this node
            root->val = successor->val;

            // Delete the in-order successor from the right subtree
            root->right = deleteNode(root->right, successor->val);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr) {
        return root;
    }

    // 2. Update height of the current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // 3. Get the balance factor to check for imbalance
    int balance = getBalance(root);

    // 4. If unbalanced, perform rotations

    // Left Left Case (LL)
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    // Left Right Case (LR)
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Right Case (RR)
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    // Right Left Case (RL)
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root; 
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

void levelorderTraversal(AVLNode* root) {
    if (!root) {
        return;
    }
    queue<AVLNode*> q;
    q.push(root);

    while (!q.empty()) {
        AVLNode* current = q.front();
        q.pop();
        cout << current->val << " (H:" << current->height << ", B:" << getBalance(current) << ") ";

        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }
    cout << endl;
}


// Deallocates all nodes in the tree to prevent memory leaks.
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

    int delete_val;
    cout << "Enter value to delete (enter 0 to stop deleting): ";
    cin >> delete_val;

    while (delete_val != 0) {
        root = deleteNode(root, delete_val);
        cout << "\n--- AVL Tree after deleting " << delete_val << " ---" << endl;
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            break;
        }
        cout << "In-order Traversal: ";
        inorderTraversal(root);
        cout << endl;

        cout << "Pre-Order Traversal: ";
        preorderTraversal(root);
        cout << endl;

        cout << "Post-Order Traversal: ";
        postorderTraversal(root);
        cout << endl;

        cout << "Level-order Traversal (Node Value, Height, Balance Factor): " << endl;
        levelorderTraversal(root);
        cout << endl;

        cout << "Enter value to delete (enter 0 to stop deleting): ";
        cin >> delete_val;
    }

    destroy(root);
    return 0;
}