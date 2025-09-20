#include <iostream>
using namespace std;

class Time{
    int hour;
    int minute;
    int second;

    void inp24format(){
        cout<<"Enter hour: "; cin>>hour;
        cout<<"Enter minute: "; cin>>minute;
        cout<<"Enter second: "; cin>>second;
    }
};