#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node *left, *right, *parent;
    Node(int val) {
        data = val;
        left = right = parent = nullptr;
    }
};

class MaxHeap {
    Node* root;

    void heapifyUp(Node* node) {
        while (node->parent && node->data > node->parent->data) {
            swap(node->data, node->parent->data);
            node = node->parent;
        }
    }

    void heapifyDown(Node* node) {
        if (!node) return;

        Node* largest = node;

        if (node->left && node->left->data > largest->data)
            largest = node->left;

        if (node->right && node->right->data > largest->data)
            largest = node->right;

        if (largest != node) {
            swap(node->data, largest->data);
            heapifyDown(largest);
        }
    }

    int getHeight(Node* node) {
        if (!node) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

public:
    MaxHeap() {
        root = nullptr;
    }

    void Insert(int val) {
        Node* newNode = new Node(val);

        if (!root) {
            root = newNode;
            return;
        }

        // Level-order traversal to find first empty spot
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();

            if (!temp->left) {
                temp->left = newNode;
                newNode->parent = temp;
                heapifyUp(newNode);
                return;
            } else q.push(temp->left);

            if (!temp->right) {
                temp->right = newNode;
                newNode->parent = temp;
                heapifyUp(newNode);
                return;
            } else q.push(temp->right);
        }
    }

    int ExtractMax() {
        if (!root) {
            cout << "Heap is empty!" << endl;
            return -1;
        }

        int maxVal = root->data;

        // Find last node with level-order traversal
        queue<Node*> q;
        q.push(root);
        Node* last = nullptr;
        while (!q.empty()) {
            last = q.front();
            q.pop();
            if (last->left) q.push(last->left);
            if (last->right) q.push(last->right);
        }

        if (last == root) {
            delete root;
            root = nullptr;
            return maxVal;
        }

        // Replace root with last node’s value
        root->data = last->data;

        // Remove last node
        if (last->parent->left == last)
            last->parent->left = nullptr;
        else
            last->parent->right = nullptr;

        delete last;

        // Heapify down
        heapifyDown(root);

        return maxVal;
    }

    void LevelOrder() {
        if (!root) {
            cout << "Heap is empty!";
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();
            cout << temp->data << " ";
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
    }

    void PreOrder() { preorder(root); }
    void InOrder() { inorder(root); }
    void PostOrder() { postorder(root); }
    int Height() { return getHeight(root); }
    void Display() { LevelOrder(); }
};

int main() {
    MaxHeap H;

    int option = -1;
    while(option != 8) {
        cout << "\n\n----------------------------------------------------";
        cout << "\n\n\t\tMAX HEAP : MENU";
        cout << "\n1. Display heap (Level Order)";
        cout << "\n2. Height of heap";
        cout << "\n3. Insert node";
        cout << "\n4. Extract max (Delete root)";
        cout << "\n5. Pre-order traversal";
        cout << "\n6. Post-order traversal";
        cout << "\n7. In-order traversal";
        cout << "\n8. Exit";
        cout << "\n--> Select any one of the above options (1-8) : ";
        cin.sync();
        cin >> option;

        switch(option) {
            case 1: {
                cout << "\nHeap (Level Order): ";
                H.Display();
            } break;
            case 2: {
                cout << "\nHeight of heap = " << H.Height();
            } break;
            case 3: {
                int x;
                cout << "\nInsert node value : ";
                cin >> x;        
                H.Insert(x);
            } break;
            case 4: {
                int maxVal = H.ExtractMax();
                if(maxVal != -1)
                    cout << "\nExtracted max = " << maxVal;
            } break;
            case 5: {
                cout << "\nPre-order traversal : ";
                H.PreOrder();
            } break;
            case 6: {
                cout << "\nPost-order traversal : ";
                H.PostOrder();
            } break;
            case 7: {
                cout << "\nIn-order traversal : ";
                H.InOrder();
            } break;
            case 8: {
                return 0;
            } break;
            default: cout << "\nWrong option selected !!";
        }
    }

    return 0;
}
