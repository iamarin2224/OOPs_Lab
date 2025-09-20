#include <iostream>
using namespace std;

void f(int x) {
    cout << "inside f(int)" << endl;
}

void f(float x) {
    cout << "inside f(float)" << endl;
}

int main() {
    int i = 10;
    char c = 'A';
    float f1 = 3.14;
    double d = 5.67;

    cout << "Calling f with int:" << endl;
    f(i);

    cout << "Calling f with char:" << endl;
    f(c);

    cout << "Calling f with float:" << endl;
    f(f1);

    //cout << "Calling f with double:" << endl;
    // f(d);
    //The code cant be executed due to "error: call to 'f' is ambiguous" 

    return 0;
}
