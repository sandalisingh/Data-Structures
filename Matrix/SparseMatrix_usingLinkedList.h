#include <iostream>
using namespace std;

#ifndef SparseMatrix_h
#define SparseMatrix_h

struct Node {
    int row, col, val;
    Node* next;
};

class SparseMatrix {
public:
    int rows, cols;
    Node* head;   

    SparseMatrix(int r, int c) {
        rows = r;
        cols = c;
        head = nullptr;
    }

    void Insert(int r, int c, int v) {
        Node* temp = new Node;
        temp->row = r;
        temp->col = c;
        temp->val = v;
        temp->next = nullptr;

        if (head == nullptr) {
            // list is empty
            // insert at beginning
            head = temp;
        } else {
            // add at the end
            Node* p = head;
            while (p->next != nullptr)
                p = p->next;
            p->next = temp;
        }
    }

    void Create(int n) {
        cout << "Enter all non-zero elements (row col value):\n";
        for (int i = 0; i < n; i++) {
            int r, c, v;
            cout << "Element " << (i+1) << "\n\t- Row : ";
            cin >> r;
            cout << "\t- Col : ";
            cin >> c;
            cout << "\t- Value : ";
            cin >> v;
            Insert(r, c, v);
        }
    }

    void Display() {
        Node* p = head;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (p != nullptr && p->row == i && p->col == j) {
                    cout << p->val << " ";
                    p = p->next;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    ~SparseMatrix() {
        Node* p = head;
        while (p != nullptr) {
            Node* q = p;
            p = p->next;
            delete q;
        }
    }
};

int main() {
    int rows, cols, n, choice;
    
    cout << "Enter dimensions of the Sparse Matrix";
    cout << "\n\t- Rows : ";
    cin >> rows;
    cout << "\t- Cols : ";
    cin >> cols;
    
    SparseMatrix sm(rows, cols);
    
    do {
        cout << "\n1. Insert elements\n";
        cout << "2. Display matrix\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                cout << "Enter number of non-zero elements: ";
                cin >> n;
                sm.Create(n);
                break;
            case 2:
                cout << "\nSparse Matrix:\n";
                sm.Display();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 3);

    return 0;
}

#endif 