#include <iostream>
using namespace std;

#include "SparseMatrix_usingLinkedList.h"

// Separate add function
SparseMatrix add(const SparseMatrix& m1, const SparseMatrix& m2) {
    if (m1.rows != m2.rows || m1.cols != m2.cols) {
        throw runtime_error("Matrix dimensions must match for addition");
    }

    SparseMatrix result(m1.rows, m1.cols);
    int i = 0, j = 0;

    // Merge two linked-list based sparse matrices (row-major order)
    Node* p = m1.head;
    Node* q = m2.head;

    while (p != nullptr && q != nullptr) {
        if (p->row < q->row || (p->row == q->row && p->col < q->col)) {
            result.Insert(p->row, p->col, p->val);
            p = p->next;
        } else if (p->row > q->row || (p->row == q->row && p->col > q->col)) {
            result.Insert(q->row, q->col, q->val);
            q = q->next;
        } else {
            // in case of same position
            int s = p->val + q->val;
            if (s != 0) result.Insert(p->row, p->col, s);
            p = p->next;
            q = q->next;
        }
    }

    while (p != nullptr) {
        result.Insert(p->row, p->col, p->val);
        p = p->next;
    }

    while (q != nullptr) {
        result.Insert(q->row, q->col, q->val);
        q = q->next;
    }

    return result;
}

int main() {
    int rows, cols;
    cout << "Enter number of rows and columns: ";
    if (!(cin >> rows >> cols)) return 0;

    int n1;
    cout << "Enter number of non-zero elements in first matrix: ";
    cin >> n1;
    SparseMatrix matrix1(rows, cols);
    cout << "Enter row col value for each non-zero element (one per line):\n";
    for (int k = 0; k < n1; ++k) {
        int r, c, v;
        cin >> r >> c >> v;
        matrix1.Insert(r, c, v);
    }

    int n2;
    cout << "Enter number of non-zero elements in second matrix: ";
    cin >> n2;
    SparseMatrix matrix2(rows, cols);
    cout << "Enter row col value for each non-zero element (one per line):\n";
    for (int k = 0; k < n2; ++k) {
        int r, c, v;
        cin >> r >> c >> v;
        matrix2.Insert(r, c, v);
    }

    SparseMatrix result = add(matrix1, matrix2);
    cout << "Result (non-zero elements):\n";
    cout << "Row Col Value\n";
    Node* t = result.head;
    while (t != nullptr) {
        cout << t->row << " " << t->col << " " << t->val << "\n";
        t = t->next;
    }

    return 0;
}
