#include <iostream>
using namespace std;

void f(int x, int y) {
    cout << "inside f(int, int)" << endl;
}

void f(char c, int y) {
    cout << "inside f(char, int)" << endl;
}

int main() {
    int i = 10;
    char c = 'A';
    float f1 = 3.14;

    cout << "Calling f(int, char):" << endl;
    f(i, c);

    cout << "Calling f(char, char):" << endl;
    f(c, c);

    // cout << "Calling f(float, float):" << endl;
    // f(f1, f1);
    //The code cant be executed due to "error: call to 'f' is ambiguous" 

    return 0;
}