#include <iostream>
using namespace std;

struct Student
{
    int roll;
    float score;

    void inputDetails(){
        cout<<"Enter roll: "; cin>>roll;
        cout<<"Enter score: "; cin>>score;
    }

    void showDetails(){
        cout<<"Student with roll: "<<roll<<" has score: "<<score<<endl;
    }

    friend void update(Student &);
    friend void displayUpdated(Student &);
};

void update(Student &stu){
    cout<<"\nEnter new score: "; cin>>stu.score;
}

void displayUpdated(Student &stu){
    cout<<"Student with roll: "<<stu.roll<<" now has score: "<<stu.score<<endl;
}

int main(){
    Student stu;

    stu.inputDetails();
    stu.showDetails();

    update(stu);
    displayUpdated(stu);

    return 0;
}