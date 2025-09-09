#include <iostream>
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
public:
    int n;
    Node* min;
    Node* rootList;

    FibonacciHeap() {
        n = 0;
        min = nullptr;
        rootList = nullptr;
    }
};
