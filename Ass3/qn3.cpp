#include <iostream>
using namespace std;

float calcTax(float income, float taxRate = 10){
    return income * (taxRate/100.0);
}

int main(){
    float income;
    cout<<"Enter income: ";
    cin>>income;

    float tax = calcTax(income);
    cout<<"Calculated tax with default rate: "<<tax<<endl;

    int taxRate;
    cout<<"\nEnter custom tax rate(in percent): ";
    cin>>taxRate;

    tax = calcTax(income, taxRate);
    cout<<"\nCalculated tax with custom rate: "<<tax<<endl;

    return 0;
}