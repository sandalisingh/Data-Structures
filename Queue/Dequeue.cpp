#include<iostream>
using namespace std;

//---------------------- D E Q U E   C L A S S---------------------------

class Deque{
    int  *Q;
    int  front;
    int  rear;
    int  size;

    public :

        Deque();
        Deque(int size);

        void  insertfront(int key);
        void  insertrear(int key);

        void  deletefront();
        void  deleterear();

        bool  isFull();
        bool  isEmpty();

        int  getFront();
        int  getRear();

        void Display();
};

//---------------------- F X N S---------------------------

Deque :: Deque(){
    size = 5;
    front =  -1;
    rear = -1;
    Q = new int[size];
}

Deque :: Deque(int size){
    front = -1;
    rear = -1;
    this->size = size;
    Q = new int[size];
}

bool Deque :: isEmpty(){
    if(front == -1){
        return true;
    }else{
        return false;
    }
}

bool Deque :: isFull(){
    if((rear + 1) % size == front){
        return true;
    }else{
        return false;
    }
}


void Deque :: Display(){  
    if(isEmpty()) {
        cout << "\nEmpty!\n";
        return;
    }
    
    if(rear >= front){
        for(int i = front; i <= rear; i++){
            cout<<Q[i]<<" ";
        }
    }else{
        for(int i = 0; i <= rear; i++){
            cout<<Q[i]<<" ";
        }
        for(int i = rear + 1; i < front; i++){
            cout<<"- ";
        }
        for(int i = front; i < size; i++){
            cout<<Q[i]<<" ";
        }
    }

    cout<<endl;
}

void Deque :: insertfront(int key){
    if (isFull()){
        cout << "\nOVERFLOW!\n";
        return;
    }
    if (front == -1){   //adding 1st element
        front = 0;
        rear = 0;
    }else if ((front == 0) && (rear != (size - 1))){
        front = size - 1 ;
    }else{ 
        front = front - 1;
    }
    Q[front] = key ;
}

void Deque :: insertrear(int key){
    if (isFull()){
        cout << "\nOVERFLOW!\n";
        return;
    }
    if (front == -1){
        front = 0;
        rear = 0;
    }else if ((rear == size - 1) && (front != 0)){
        rear = 0;
    }else{
        rear = rear + 1;
    }
    Q[rear] = key ;
}

void Deque :: deletefront(){
    if(isEmpty()){
        cout<<"\nUNDERFLOW!\n"<<endl;
        return;
    }
    if (front == rear){
        front = -1;
        rear = -1;
    }else{
        if (front == size -1){
            front = 0;
        }else {
            front = front + 1;
        }
    }
}

void Deque :: deleterear(){
    if(isEmpty()){
        cout<<"\nUNDERFLOW!\n"<<endl;
        return;
    }
    if (front == rear){
        front = -1;
        rear = -1;
    }else if (rear == 0){
        rear = size-1;
    }else{
        rear = rear - 1;
    }
}

int Deque :: getFront(){
    if (isEmpty()){
        cout<<"\nUNDERFLOW!\n"<<endl;
        return -1 ;
    }
    return Q[front];
}

int Deque :: getRear(){
    if(isEmpty() || rear < 0){
        cout<<"\nUNDERFLOW!\n"<<endl;
        return -1 ;
    }
    return Q[rear];
}

int main(){
    Deque Q;
    int ch;
    do {
        cout<<"\n\nCQ"; 
        cout << "\n1.Insert Front";
        cout << "\t2.Insert Rear";
        cout << "\n3.Delete Front";
        cout << "\t4.Delete Rear";
        cout << "\n5.Front"; 
        cout << "\t\t6.Rear";
        cout << "\n7.Display"; 
        cout << "\t8. Exit";
        int choice;
        cout << "\nChoice : ";
        cin >> choice;
        switch (choice){
                case 1:{
                    int insert;
                    cout << "\nEnqueue : "; 
                    cin >> insert;
                    Q.insertfront(insert);
                }break;
                case 2:{
                    int insert;
                    cout << "\nEnqueue : "; 
                    cin >> insert;
                    Q.insertrear(insert);
                }break;
                case 3:{
                    Q.deletefront(); 
                }break;
                case 4:{
                    Q.deleterear(); 
                }break;
                case 5:{
                    int x = Q.getFront(); 
                    if(x != -1){
                        cout<<"\nFront = "<<x;
                    }
                }break;
                case 6:{
                    int x = Q.getRear(); 
                    if(x != -1){
                        cout<<"\nRear = "<<x;
                    }
                }break;
                case 7:{
                    Q.Display();
                } break;
                case 8: return 0;
                default:{
                    cout<<"\nWRONG!\n";
                }
            }
        } while(true); 
    return 0;
}