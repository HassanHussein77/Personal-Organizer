#ifndef UTILITY_H
#define UTILITY_H

#include<string>
#include<chrono>

using namespace std;
//This function returns the current day,date and time in a string
inline string setDateAndTime() {
    auto currentTime = chrono::system_clock::now();
    time_t currentTime2 = chrono::system_clock::to_time_t(currentTime);

    char timeBuffer[26];
    ctime_s(timeBuffer, sizeof(timeBuffer), &currentTime2);

    string time(timeBuffer);
    return time;
}

#endif