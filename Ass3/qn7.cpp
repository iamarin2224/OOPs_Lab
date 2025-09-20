#include <iostream>
using namespace std;

class Time{
    int hour;
    int minute;
    int second;

public:

    void inp24hformat(){
        cout<<"Enter hour (in 24h format): "; cin>>hour;
        cout<<"Enter minute: "; cin>>minute;
        cout<<"Enter second: "; cin>>second;
    }

    void inp12hformat(){
        int tempHr;
        cout<<"Enter hour (in 12h format): "; cin>>tempHr;
        cout<<"Enter minute: "; cin>>minute;
        cout<<"Enter second: "; cin>>second;

        string period;
        cout<<"Enter time period (AM or PM): "; cin>>period;
        if (!(period == "am" || period == "pm")){
            cout<<"Invalid period!\n";
            return;
        }

        if (period == "am"){
            if (tempHr != 12){
                hour = tempHr;
            }
            else{
                hour = 0;
            }
        }
        else{
            if (tempHr != 12){
                hour = tempHr+12;
            }
            else{
                hour = tempHr;
            }
        }
    }

    void display24h(){
        cout<<"\nTime is- "<<hour<<":"<<minute<<":"<<second<<endl;
    }

    void display12h(){
        if (hour<12 && hour!=0){
            cout<<"\nTime is- "<<hour<<":"<<minute<<":"<<second<<" AM"<<endl;
        }
        else if (hour>12){
            cout<<"\nTime is- "<<hour-12<<":"<<minute<<":"<<second<<" PM"<<endl;
        }
        else if (hour == 0){
            cout<<"\nTime is- "<<"12"<<":"<<minute<<":"<<second<<" AM"<<endl;
        }
        else if (hour == 12){
            cout<<"\nTime is- "<<"12"<<":"<<minute<<":"<<second<<" PM"<<endl;
        }
    }

    void addMinute(){
        int mins;
        cout<<"Enter minutes to add: "; cin>>mins;

        if ((mins+minute)<60){
            minute = mins+minute;
        }

        else{
            minute = (mins+minute) - 60;
            if (hour != 23){
                hour += 1;
            }
            else{
                hour = 0;
            }
        }
    }
};

int main(){
    Time t;

    int choice;

    do
    {
        cout<<"\n\n------ MENU ------\n\
        0. Exit \n\
        1. Enter new time in 12h format \n\
        2. Enter new time in 24h format \n\
        3. Display time in 12h format \n\
        4. Display time in 24h format \n\
        5. Add minutes to time \n";

        cout<<"Enter you choice: ";
        cin>>choice;

        switch (choice)
        {
        case 0:
            cout<<"Exiting...\n";
            break;
        case 1:
            t.inp12hformat();
            break;
        case 2:
            t.inp24hformat();
            break;
        case 3:
            t.display12h();
            break;
        case 4:
            t.display24h();
            break;
        case 5:
            t.addMinute();
            break;
        default:
            cout<<"Enter valid choice!\n";
            break;
        }

    } while (choice != 0);
    
    return 0;
}