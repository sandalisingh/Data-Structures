#include <iostream>
using namespace std;

// Node structure for Binomial Heap
struct Node {
    int key;
    int degree;
    Node* parent;
    Node* child;
    Node* sibling;

    Node(int value) : key(value), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

class BinomialHeap {
private:
    Node* head;

    // Merge two binomial heaps
    Node* merge(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        Node* result = nullptr;
        Node** curr = &result;

        while (h1 && h2) {
            if (h1->degree <= h2->degree) {
                *curr = h1;
                h1 = h1->sibling;
            } else {
                *curr = h2;
                h2 = h2->sibling;
            }
            curr = &((*curr)->sibling);
        }

        if (h1) *curr = h1;
        if (h2) *curr = h2;

        return result;
    }

    // Link two binomial trees of same degree
    void link(Node* y, Node* z) {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree++;
    }

    // Union of two binomial heaps
    Node* unionHeap(Node* h1, Node* h2) {
        Node* newHead = merge(h1, h2);
        if (!newHead) return nullptr;

        Node* prev = nullptr;
        Node* curr = newHead;
        Node* next = curr->sibling;

        while (next) {
            if (curr->degree != next->degree || 
                (next->sibling && next->sibling->degree == curr->degree)) {
                prev = curr;
                curr = next;
            } else {
                if (curr->key <= next->key) {
                    curr->sibling = next->sibling;
                    link(next, curr);
                } else {
                    if (!prev)
                        newHead = next;
                    else
                        prev->sibling = next;
                    link(curr, next);
                    curr = next;
                }
            }
            next = curr->sibling;
        }
        return newHead;
    }

public:
    BinomialHeap() : head(nullptr) {}

    // Insert a new key into the heap
    void insert(int key) {
        Node* newNode = new Node(key);
        head = unionHeap(head, newNode);
    }

    // Get minimum key from the heap
    int getMin() {
        if (!head) throw runtime_error("Heap is empty");

        Node* y = head;
        int min = y->key;
        while (y->sibling) {
            y = y->sibling;
            if (y->key < min)
                min = y->key;
        }
        return min;
    }

    // Extract minimum key from the heap
    int extractMin() {
        if (!head) throw runtime_error("Heap is empty");

        Node* minNode = head;
        Node* minPrev = nullptr;
        Node* curr = head->sibling;
        Node* prev = head;

        // Find minimum node
        while (curr) {
            if (curr->key < minNode->key) {
                minNode = curr;
                minPrev = prev;
            }
            prev = curr;
            curr = curr->sibling;
        }

        // Remove minimum node
        if (minPrev)
            minPrev->sibling = minNode->sibling;
        else
            head = minNode->sibling;

        // Reverse the order of children
        Node* newHead = nullptr;
        Node* child = minNode->child;
        while (child) {
            Node* next = child->sibling;
            child->sibling = newHead;
            child->parent = nullptr;
            newHead = child;
            child = next;
        }

        int minKey = minNode->key;
        delete minNode;

        // Union the remaining heap with the reversed children
        head = unionHeap(head, newHead);
        return minKey;
    }

    // Check if heap is empty
    bool isEmpty() {
        return head == nullptr;
    }
};

int main() {
    BinomialHeap heap;
    while (true) {
        cout << "\n\nBinomial Heap Operations:";
        cout << "\n1. Insert";
        cout << "\n2. Extract Min";
        cout << "\n3. Get Min";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                cout << "Enter value to insert: ";
                cin >> value;
                heap.insert(value);
                cout << "Inserted " << value;
                break;
            }
            case 2: {
                if (!heap.isEmpty()) {
                    int min = heap.extractMin();
                    cout << "Extracted minimum: " << min;
                } else {
                    cout << "Heap is empty";
                }
                break;
            }
            case 3: {
                if (!heap.isEmpty()) {
                    cout << "Minimum value: " << heap.getMin();
                } else {
                    cout << "Heap is empty";
                }
                break;
            }
            case 4:
                return 0;
            default:
                cout << "Invalid choice!";
        }
    }
    return 0;
}