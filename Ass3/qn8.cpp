#include <iostream>
using namespace std;

class Stack{
    int arr[100];
    int size = 0;
    int back = 0;

    public:
    void initialize(int val){
        if (size!=0){
            cout<<"Stack already initialized!"<<endl;
            return;
        }
        arr[0] = val;
        back = 1;
        size = 1;
    }

    void pushBack(int val){
        if (size == 100){
            cout<<"OVERFLOW!"<<endl;
            return;
        }
        arr[back] = val;
        back++;
        size++;
    }

    int popBack(){
        if (size == 0){
            cout<<"UNDERFLOW!"<<endl;
            return 0;
        }
        size--;
        back--;

        return arr[back];
    }

    void printStack(){
        for (int i=0; i<size; i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
};

int main(){
    Stack st;

    st.initialize(45);
    st.pushBack(56);
    st.printStack();

    st.pushBack(12);
    st.pushBack(28);
    st.pushBack(47);
    st.printStack();

    st.popBack();
    st.popBack();
    st.pushBack(9);
    st.printStack();

    return 0;
}