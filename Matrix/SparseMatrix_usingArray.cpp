#include <iostream>
using namespace std;

struct Element {
    int row;
    int col;
    int val;
};

class SparseMatrix {
private:
    int rows, cols, num;  // rows, cols, and number of non-zero elements
    Element *ele;         // dynamic array for non-zero elements

public:
    SparseMatrix(int r, int c, int n);
    ~SparseMatrix();
    void Create();
    void Display();
};

SparseMatrix :: SparseMatrix(int r, int c, int n) {
    rows = r;
    cols = c;
    num = n;
    ele = new Element[num];
}

SparseMatrix :: ~SparseMatrix() {
    delete[] ele;
}

void SparseMatrix :: Create() {
    cout << "Enter all non-zero elements (row col value):\n";
    for (int i = 0; i < num; i++) {
        cout << "Element " << (i+1) << "\n\t- Row : ";
        cin >> ele[i].row;
        cout << "\t- Col : ";
        cin >> ele[i].col;
        cout << "\t- Value : ";
        cin >> ele[i].val;
    }
}

void SparseMatrix :: Display() {
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (k < num && ele[k].row == i && ele[k].col == j)
                cout << ele[k++].val << " ";
            else
                cout << "0 ";
        }
        cout << endl;
    }
}

int main() {
    int rows, cols, n;
    cout << "Enter dimensions of the Sparse Matrix";
    cout << "\n\t- Rows : ";
    cin >> rows ;
    cout << "\t- Cols : ";
    cin >> cols;
    cout << "Enter number of non-zero elements: ";
    cin >> n;

    SparseMatrix SM(rows, cols, n);
    SM.Create();

    cout << "\nSparse Matrix:\n";
    SM.Display();

    return 0;
}
