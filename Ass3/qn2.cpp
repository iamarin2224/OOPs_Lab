#include <iostream>
using namespace std;

int &maxM(int &a, int &b){
    return (a > b) ? a : b;
}

int main(){
    int a, b;
    cout<<"Enter number 1: "; cin>>a;
    cout<<"Enter number 2: "; cin>>b;

    int x = maxM(a, b);
    cout << "\nCase i :\n";
    cout << "Before modifying x: a = " << a << ", b = " << b << ", x = " << x << endl;
    x = 1089; 
    cout << "After modifying x: a = " << a << ", b = " << b << ", x = " << x << endl;

    int &y = maxM(a, b);
    cout << "\nCase ii (x as reference):\n";
    cout << "Before modifying x: a = " << a << ", b = " << b << ", x = " << y << endl;
    y = 1089; 
    cout << "After modifying x: a = " << a << ", b = " << b << ", x = " << y << endl;

    return 0;
}