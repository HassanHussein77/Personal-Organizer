#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "organizerItem.h"
#include "reminderFeature.h"

#include <sstream>

using namespace std;
//Appointment Class (inherits attributes and methods from organizeritem and reminderfeature classes)
//It is used to keep track of appointments using different attributes
class Appointment : public OrganizerItem, public ReminderFeature {
private:
    string startTime;
    string endTime;
    string location;
    vector<string> attendees;
public:
    //constructor
    Appointment(string titleSetter = "", string descriptionSetter = "", string categorySetter = "", string startTimeSetter = "", string endTimeSetter = "", string locationSetter = "", const vector<string>& d = {}, string reminderSetter = "")
        : OrganizerItem(titleSetter, descriptionSetter, categorySetter), attendees(d), ReminderFeature(reminderSetter) {
        startTime = startTimeSetter;
        endTime = endTimeSetter;
        location = locationSetter;
    }

    //getter Functions
    string getStartTime() {
        return startTime;
    }

    string getEndTime() {
        return endTime;
    }

    string getLocation() {
        return location;
    }

    vector<string>& getAttendees() {
        return attendees;
    }

    //setter functions
    void setStartAndEndTime(string startTimeSetter = "", string endTimeSetter = "") {
        startTime = startTimeSetter;
        endTime = endTimeSetter;
    }

    void setLocation(string& setter) {
        location = setter;
    }

    void setAttendees(const vector<string>& d) {
        attendees = d;
    }

    //updating the attendees vector
    void updatingAttendees(string attendeesInput) {
        stringstream ss(attendeesInput);
        string individualAttendee;
        this->attendees.clear();
        while (getline(ss, individualAttendee, ',')) {
            // Trim leading and trailing whitespaces
            size_t start = individualAttendee.find_first_not_of(" \t");
            size_t end = individualAttendee.find_last_not_of(" \t");

            if (start != string::npos && end != string::npos) {
                attendees.push_back(individualAttendee.substr(start, end - start + 1));
            }
        }
    }

    //override function
    void display(RenderWindow& window, Sprite background, int& xCor, int& yCor) override {
        //setting font
        Font font;
        if (!font.loadFromFile("fonts/Roboto-Medium.ttf")) {
            cerr << "Error loading font file " << endl;
            return;
        }

        //drawing title
        Text titleText("Title: " + getTitle(), font, 18);
        titleText.setFillColor(Color::White);
        yCor += 20;
        titleText.setPosition(xCor, yCor);
        window.draw(titleText);

        //drawing description
        Text descriptionText("Description: " + getDescription(), font, 18);
        yCor += 20;
        descriptionText.setPosition(xCor, yCor);
        descriptionText.setFillColor(Color::White);
        window.draw(descriptionText);

        //drawing category
        Text categoryText("Category: " + getCategory(), font, 18);
        yCor += 20;
        categoryText.setPosition(xCor, yCor);
        categoryText.setFillColor(Color::White);
        window.draw(categoryText);

        //drawing creation date
        Text creationDateText("Creation Date: " + getCreationDate(), font, 18);
        yCor += 20;
        creationDateText.setPosition(xCor, yCor);
        creationDateText.setFillColor(Color::White);
        window.draw(creationDateText);

        //drawing last modified date
        Text lastModifiedDateText("Last Modified Date: " + getLastModifiedDate(), font, 18);
        yCor += 20;
        lastModifiedDateText.setPosition(xCor, yCor);
        lastModifiedDateText.setFillColor(Color::White);
        window.draw(lastModifiedDateText);

        //drawing start time
        Text startTimeText("Start Time: " + getStartTime(), font, 18);
        yCor += 20;
        startTimeText.setPosition(xCor, yCor);
        startTimeText.setFillColor(Color::White);
        window.draw(startTimeText);

        //drawing end time
        Text endTimeText("End Time: " + getEndTime(), font, 18);
        yCor += 20;
        endTimeText.setPosition(xCor, yCor);
        endTimeText.setFillColor(Color::White);
        window.draw(endTimeText);

        //drawing location
        Text locationText("Location: " + getLocation(), font, 18);
        yCor += 20;
        locationText.setPosition(xCor, yCor);
        locationText.setFillColor(Color::White);
        window.draw(locationText);

        //drawing attendees
        Text attendeeText("Attendees: ", font, 18);
        yCor += 20;
        attendeeText.setPosition(xCor, yCor);
        attendeeText.setFillColor(Color::White);
        window.draw(attendeeText);
        xCor += 130;
        for (size_t i = 0; i < attendees.size(); ++i) {
            Text attendeeText(attendees[i], font, 18);
            attendeeText.setFillColor(Color::White);

            if (i < attendees.size() - 1) {
                attendeeText.setString(attendees[i] + ", ");
            }

            attendeeText.setPosition(xCor, yCor);
            window.draw(attendeeText);
            xCor += 90;
        }

        //drawing reminder
        Text reminderText("Reminder: " + getReminder(), font, 18);
        xCor = 20;
        yCor += 20;
        reminderText.setPosition(xCor, yCor);
        reminderText.setFillColor(Color::White);
        window.draw(reminderText);
    }

};
#endif