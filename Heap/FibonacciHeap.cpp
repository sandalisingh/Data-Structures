#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Node {
public:
    int key;
    int degree;
    bool mark;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;

    Node(int k) {
        key = k;
        degree = 0;
        mark = false;
        parent = child = left = right = nullptr;
    }
};

class FibonacciHeap {
private:
    int n;
    Node* min;
    
    void link(Node* y, Node* x) {
        // Remove y from root list
        y->left->right = y->right;
        y->right->left = y->left;
        
        // Make y a child of x
        y->parent = x;
        if (!x->child) {
            x->child = y;
            y->right = y;
            y->left = y;
        } else {
            y->right = x->child->right;
            y->left = x->child;
            x->child->right->left = y;
            x->child->right = y;
        }
        
        x->degree++;
        y->mark = false;
    }
    
    void consolidate() {
        int max_degree = log2(n) + 1;
        vector<Node*> A(max_degree, nullptr);
        
        // Create list of roots
        vector<Node*> roots;
        Node* current = min;
        do {
            roots.push_back(current);
            current = current->right;
        } while (current != min);
        
        for (Node* w : roots) {
            Node* x = w;
            int d = x->degree;
            while (A[d] != nullptr) {
                Node* y = A[d];
                if (x->key > y->key) {
                    swap(x, y);
                }
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        }
        
        min = nullptr;
        for (int i = 0; i < max_degree; i++) {
            if (A[i] != nullptr) {
                if (min == nullptr) {
                    min = A[i];
                    min->left = min;
                    min->right = min;
                } else {
                    A[i]->right = min->right;
                    A[i]->left = min;
                    min->right->left = A[i];
                    min->right = A[i];
                    if (A[i]->key < min->key) {
                        min = A[i];
                    }
                }
            }
        }
    }
    
    void cut(Node* x, Node* y) {
        // Remove x from child list of y
        if (x->right == x) {
            y->child = nullptr;
        } else {
            y->child = x->right;
            x->left->right = x->right;
            x->right->left = x->left;
        }
        y->degree--;
        
        // Add x to root list
        x->right = min->right;
        x->left = min;
        min->right->left = x;
        min->right = x;
        x->parent = nullptr;
        x->mark = false;
    }
    
    void cascadingCut(Node* y) {
        Node* z = y->parent;
        if (z != nullptr) {
            if (!y->mark) {
                y->mark = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

public:
    FibonacciHeap() {
        n = 0;
        min = nullptr;
    }
    
    void insert(int key) {
        Node* x = new Node(key);
        if (min == nullptr) {
            min = x;
            x->left = x;
            x->right = x;
        } else {
            x->right = min->right;
            x->left = min;
            min->right->left = x;
            min->right = x;
            if (x->key < min->key) {
                min = x;
            }
        }
        n++;
    }
    
    Node* getMin() {
        return min;
    }
    
    Node* extractMin() {
        Node* z = min;
        if (z != nullptr) {
            if (z->child != nullptr) {
                Node* child = z->child;
                do {
                    Node* next = child->right;
                    child->right = min->right;
                    child->left = min;
                    min->right->left = child;
                    min->right = child;
                    child->parent = nullptr;
                    child = next;
                } while (child != z->child);
            }
            
            z->left->right = z->right;
            z->right->left = z->left;
            
            if (z == z->right) {
                min = nullptr;
            } else {
                min = z->right;
                consolidate();
            }
            n--;
        }
        return z;
    }
    
    void decreaseKey(Node* x, int k) {
        if (k > x->key) {
            cout << "New key is greater than current key" << endl;
            return;
        }
        x->key = k;
        Node* y = x->parent;
        if (y != nullptr && x->key < y->key) {
            cut(x, y);
            cascadingCut(y);
        }
        if (x->key < min->key) {
            min = x;
        }
    }
    
    void deleteNode(Node* x) {
        decreaseKey(x, INT_MIN);
        extractMin();
    }
    
    void merge(FibonacciHeap& other) {
        if (other.min == nullptr) return;
        if (min == nullptr) {
            min = other.min;
        } else {
            Node* temp = min->right;
            min->right = other.min->right;
            other.min->right->left = min;
            other.min->right = temp;
            temp->left = other.min;
            
            if (other.min->key < min->key) {
                min = other.min;
            }
        }
        n += other.n;
        other.min = nullptr;
        other.n = 0;
    }
};

int main() {
    FibonacciHeap heap;
    while (true) {
        cout << "\n\nFibonacci Heap Operations:";
        cout << "\n1. Insert";
        cout << "\n2. Extract Min";
        cout << "\n3. Decrease Key";
        cout << "\n4. Delete Node";
        cout << "\n5. Get Min";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int key;
                cout << "Enter key to insert: ";
                cin >> key;
                heap.insert(key);
                cout << "Key inserted successfully";
                break;
            }
            case 2: {
                Node* min = heap.extractMin();
                if (min != nullptr) {
                    cout << "Extracted minimum key: " << min->key;
                } else {
                    cout << "Heap is empty";
                }
                break;
            }
            case 3: {
                int oldKey, newKey;
                cout << "Enter old key: ";
                cin >> oldKey;
                cout << "Enter new key: ";
                cin >> newKey;
                // Note: This is simplified. In practice, you need to find the node first
                // heap.decreaseKey(node, newKey);
                cout << "Please note: decrease key requires node reference";
                break;
            }
            case 4: {
                int key;
                cout << "Enter key to delete: ";
                cin >> key;
                // Note: This is simplified. In practice, you need to find the node first
                // heap.deleteNode(node);
                cout << "Please note: delete requires node reference";
                break;
            }
            case 5: {
                Node* min = heap.getMin();
                if (min != nullptr) {
                    cout << "Minimum key: " << min->key;
                } else {
                    cout << "Heap is empty";
                }
                break;
            }
            case 6:
                return 0;
            default:
                cout << "Invalid choice!";
        }
    }
    return 0;
}
