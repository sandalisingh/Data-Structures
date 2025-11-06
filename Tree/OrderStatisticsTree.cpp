#include <iostream>
using namespace std;

// Simple Treap-based Order Statistics Tree
struct Node {
    int key;
    int pr;
    int cnt;    // count of equal keys
    int sz;     // size of subtree (including duplicates)
    Node *l, *r;
    Node(int k, int p) : key(k), pr(p), cnt(1), sz(1), l(nullptr), r(nullptr) {}
};

int sz(Node* t){ return t ? t->sz : 0; }
void upd(Node* t){ if(t) t->sz = sz(t->l) + sz(t->r) + t->cnt; }

void rotateLeft(Node*& t){
    Node* r = t->r;
    t->r = r->l;
    r->l = t;
    upd(t); upd(r);
    t = r;
}
void rotateRight(Node*& t){
    Node* l = t->l;
    t->l = l->r;
    l->r = t;
    upd(t); upd(l);
    t = l;
}

void insert(Node*& t, int key, int pr){
    if(!t){
        t = new Node(key, pr);
        return;
    }
    if(key == t->key){
        t->cnt++;
    } else if(key < t->key){
        insert(t->l, key, pr);
        if(t->l->pr > t->pr) rotateRight(t);
    } else {
        insert(t->r, key, pr);
        if(t->r->pr > t->pr) rotateLeft(t);
    }
    upd(t);
}

// returns kth smallest (1-based). Throws out_of_range if k invalid.
int kth(Node* t, int k){
    if(!t || k <= 0 || k > sz(t)) throw out_of_range("k out of range");
    int leftSize = sz(t->l);
    if(k <= leftSize) return kth(t->l, k);
    if(k <= leftSize + t->cnt) return t->key;
    return kth(t->r, k - leftSize - t->cnt);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << "Enter n (number of elements): ";
    int n;
    if(!(cin >> n) || n < 0) return 0;
    cout << "Enter " << n << " integers:\n";
    vector<int> a(n);
    for(int i = 0; i < n; ++i) cin >> a[i];

    // build treap
    mt19937 rng((uint32_t)chrono::high_resolution_clock::now().time_since_epoch().count());
    Node* root = nullptr;
    for(int v : a) insert(root, v, (int)rng());

    cout << "Tree built. Total elements (with duplicates): " << sz(root) << "\n";
    cout << "Enter k to get k-th smallest (1-based). Enter 0 to exit.\n";
    while(true){
        cout << "k = ";
        int k;
        if(!(cin >> k)) break;
        if(k == 0) break;
        try{
            int val = kth(root, k);
            cout << k << "-th smallest = " << val << "\n";
        } catch(const out_of_range&){
            cout << "k out of range (1.." << sz(root) << ")\n";
        }
    }
    return 0;
}