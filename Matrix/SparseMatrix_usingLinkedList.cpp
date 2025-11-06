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
    int rows, cols, size;
    Node* head;   

    SparseMatrix(int r, int c) {
        rows = r;
        cols = c;
        size = 0;
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

    void Create() {
        int A[rows][cols];
        cout << "\nEnter matrix values:\n";
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                cin >> A[i][j];
            }
        }

        // Convert to sparse matrix representation
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(A[i][j] != 0) {
                    Insert(i, j, A[i][j]);
                    size++;
                }
            }
        }
    }

    void Display_LinkedListForm() {
        Node* p = head;
        cout << "\nSparse Matrix (row, col, value): ";

        while (p != nullptr) {
            cout << "[" << p->row << ", " << p->col << ", " << p->val << "] ";
            p = p->next;
        }

        cout << "\n";
    }

    void Display_CompressedRowForm() {
        int rowPtr[size];
        int colInd[size];
        int values[size];

        // Fill in the column indices and values
        Node* p = head;
        int i = 0;
        while (p != nullptr) {
            rowPtr[i] = p->row;
            colInd[i] = p->col;
            values[i] = p->val;
            
            p = p->next;
            i++;
        }

        cout << "\nRows Array: ";
        for (int i = 0; i < size; i++) {
            cout << rowPtr[i] << " ";
        }
        
        cout << "\nColumns Array: ";
        for (int i = 0; i < size; i++) {
            cout << colInd[i] << " ";
        }

        cout << "\nValues Array: ";
        for (int i = 0; i < size; i++) {
            cout << values[i] << " ";
        }
        cout << "\n";
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
        cout << "2. Display matrix in Linked List Form\n";
        cout << "3. Display matrix in Compressed Row Form\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                sm.Create();
                break;
            case 2:
                sm.Display_LinkedListForm();
                break;
            case 3:
                sm.Display_CompressedRowForm();
                break;
            default:
                cout << "Exiting...\n";
        }
    } while(choice != 4);

    return 0;
}

#endif 