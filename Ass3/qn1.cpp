#include <iostream>
using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

int main(){
    int a, b;
    cout<<"Enter number 1: "; cin>>a;
    cout<<"Enter number 2: "; cin>>b;

    swap(a,b);

    cout<<"Number 1 became: "<<a<<endl;
    cout<<"Number 2 became: "<<b<<endl;

    return 0;
}