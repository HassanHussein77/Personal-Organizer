#ifndef REMINDERFEATURE_H
#define REMINDERFEATURE_H

#include <iostream>
using namespace std;

class ReminderFeature {
private:
    string reminderTime;

public:
    //constructor
    ReminderFeature(string reminderSetter = "") {
        reminderTime = reminderSetter;
    }

    //setter function
    void setReminder(string reminderSetter = "") {
        this->reminderTime = reminderSetter;
    }

    //getter function
    string getReminder() {
        return reminderTime;
    }

    bool hasReminder() {
        return !reminderTime.empty();
    }

    //displaying the reminder
    void displayReminder() {
        cout << "Reminder Time: " << reminderTime << endl;
    }
};
#endif 
