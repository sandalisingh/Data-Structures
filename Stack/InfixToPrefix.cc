#include <iostream>
using namespace std;

struct Node{    
    public:
        char val;
        Node* next;
};

class Stack{
    Node* top;
    public :
        Stack();
        void push(char);
        void pop();
        void traverse();
        bool empty();
        int peek();
};

Stack :: Stack(){
    top = NULL;
}

void Stack :: push(char x){
    Node *temp = new Node;
    if(!temp){
        cout<<"\nHeap is full!";
    }else{
        temp->val = x;
        temp->next = top;
        top = temp;
    }
}

void Stack :: pop(){
    if(top == NULL){
        //cout<<"Empty!";
        return;
    }else{
        Node *temp = top;
        top = top->next;

        //char popped = temp->val;
        delete temp;
        //cout<<"\n"<<popped<<" has been popped from the stack!";
    }
}

void Stack :: traverse(){
    cout<<"\nStack : ";
    Node *temp = top;
    while(temp != NULL){
        cout<<temp->val<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

bool Stack :: empty(){
    if(top == NULL){
        return true;
    }else{
        return false;
    }
}

int Stack :: peek(){
    if(empty()){
        return -1;
    }else{
        return top->val;
    }
}

int precedence(char x)
{
    if(x == '+' || x == '-'){
        return 1;
    }
    else if(x == '*' || x == '/'){
        return 2;
    }
    else if(x == '^'){
        return 3;
    }
    else{
        return 0;
    }
}

string InfixToPostfix(string infix, bool InfToPre){
    Stack S;
    S.push('(');
    infix = infix + ")";
    string postfix;
    int i = 0;
    int n = infix.length();
    while(i < n || !S.empty()) {
        char ch = infix[i++];
        int preced = precedence(ch);

        //OPERATOR
        if(preced != 0){
            if(InfToPre == true){
                while(!S.empty() && precedence(ch) < precedence(S.peek()) ) {
                    postfix += S.peek();    //higher or same precedence operator from stack added to postfix expr
                    S.pop(); 
                }
            }else{
                while(!S.empty() && precedence(ch) <= precedence(S.peek()) ) {
                    postfix += S.peek();    //higher or same precedence operator from stack added to postfix expr
                    S.pop(); 
                }
            }
            
            S.push(ch); //push the encountered operator onto the stack
        }
    
        //OPEN BRACKET
        else if(ch == '('){
            S.push('(');
        }

        //CLOSED BRACKET
        else if(ch == ')') {
            while(!S.empty() && S.peek() != '(')
            {
                postfix += S.peek();
                S.pop();
            }
            S.pop();
        }

        //OPERAND
        else{
            postfix += ch;
        }

        // cout<<"\n";
        // cout<<"POSTFIX : "<<postfix<<endl;
        //S.traverse();
    }
 
    // // Pop all the remaining elements from the stack
    // while(!S.empty()) {
    //     postfix += S.peek();
    //     S.pop();
    // }

    return postfix;
}

void reverse(string& s){
    int n = s.length();
 
    for (int i = 0; i < n/2; i++){
        int temp = s[i];
        s[i] = s[n-1-i];
        s[n-1-i] = temp;
    }
}

string InfixToPrefix(string infix){
    int n = infix.size();
 
    reverse(infix);
    //cout<<"\n"<<infix;
 
    for (int i = 0; i < n; i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
            i++;
        }else if (infix[i] == ')') {
            infix[i] = '(';
            i++;
        }
    }
 
    string prefix = InfixToPostfix(infix, true);
    //cout<<"\nPREFIX = "<<prefix;
    reverse(prefix);
    //cout<<"\nPREFIX = "<<prefix<<endl;
 
    return prefix;
}

int main(){
    string infix;
    cout<<"\nINFIX = ";
    cin>>infix;
    //push('(');
    cout<<endl;
    
    cout<<infix<<" TO PREFIX : ";
    cout<<InfixToPrefix(infix)<<endl<<endl;
    //cout<<"\nANSWER = ++x/*yzwu\n";

    cout<<infix<<" TO POSTFIX : ";
    cout<<InfixToPostfix(infix, false)<<endl<<endl;

    return 0;
}