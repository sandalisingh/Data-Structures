#include <iostream>
using namespace std;

struct Node {
    int row, col, val;
    Node* next;
};

class SparseMatrix {
private:
    int rows, cols;
    Node* head;   

public:
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

        if (head == nullptr)
            head = temp;
        else {
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
    int rows, cols, n;
    cout << "Enter dimensions of the Sparse Matrix";
    cout << "\n\t- Rows : ";
    cin >> rows ;
    cout << "\t- Cols : ";
    cin >> cols;
    cout << "Enter number of non-zero elements: ";
    cin >> n;

    SparseMatrix sm(rows, cols);
    sm.Create(n);

    cout << "\nSparse Matrix:\n";
    sm.Display();

    return 0;
}
