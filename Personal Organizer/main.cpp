#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <vector>
#include "menu.cpp"
using namespace sf;
using namespace std;

//This function returns the current day,date and time in a string
string setDateAndTime() {
    auto currentTime = chrono::system_clock::now();
    time_t currentTime2 = chrono::system_clock::to_time_t(currentTime);

    char timeBuffer[26];
    ctime_s(timeBuffer, sizeof(timeBuffer), &currentTime2);

    string time(timeBuffer);
    return time;
}


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

//Main Organizer Items Class
class OrganizerItem {
private:
    string title;
    string description;
    string category;
    string creationDate;
    string lastModifiedDate;

public:
    //constructor
    OrganizerItem(string titleSetter = "", string descriptionSetter = "", string categorySetter = "")
        : title(titleSetter), description(descriptionSetter), category(categorySetter) {
        creationDate = setDateAndTime();
        lastModifiedDate = setDateAndTime();
    }

    //getter functions
    string& getTitle() {
        return title;
    }

    string& getDescription() {
        return description;
    }

    string& getCategory() {
        return category;
    }

    string& getCreationDate() {
        return creationDate;
    }

    string& getLastModifiedDate() {
        return lastModifiedDate;
    }

    //setter functions
    void setTitle(string titleSetter) {
        title = titleSetter;
    }

    void setDescription(string descriptionSetter) {
        description = descriptionSetter;
    }

    void setCategory(string categorySetter) {
        category = categorySetter;
    }

    void setCreationDate() {
        creationDate = setDateAndTime();
    }

    void setLastModifiedDate() {
        lastModifiedDate = setDateAndTime();
    }

    //pure virtual display function
    virtual void display(RenderWindow& window, Sprite background, int& xCor, int& yCor) = 0;

    //destructor
    virtual ~OrganizerItem() = default;
};

//Task Class (inherits attributes and methods from organizeritem and priorityfeature classes)
//It is used to keep track of tasks using different attributes
class Task : public OrganizerItem, public PriorityFeature {
private:
    string dueDate;
    bool completed;

public:
    //constructor
    Task(string titleSetter = "", string descriptionSetter = "", string categorySetter = "", int prioritySetter = -1,
        string dueDateSetter = "", bool completionSetter = false)
        : OrganizerItem(titleSetter, descriptionSetter, categorySetter), PriorityFeature(prioritySetter) {
        dueDate = dueDateSetter;
        completed = completionSetter;
    }

    //getter Functions
    string getDueDate() const {
        return dueDate;
    }

    bool getCompletionStatus() const {
        return completed;
    }

    //setter Functions
    void setDueDate(string dueDateSetter = "") {
        dueDate = dueDateSetter;
    }

    void setCompleteTask() {
        completed = true;
    }

    //override Functions
    void display(RenderWindow& window, Sprite background, int& xCor, int& yCor) override {
        //setting font
        Font font;
        if (!font.loadFromFile("fonts/Roboto-Medium.ttf")) {
            cerr << "Error loading font file " << endl;
            return;
        }

        //drawing title
        Text titleText("Title: " + getTitle(), font, 20);
        titleText.setFillColor(Color::White);
        yCor += 25;
        titleText.setPosition(xCor, yCor);
        window.draw(titleText);

        //drawing description
        Text descriptionText("Description: " + getDescription(), font, 20);
        yCor += 25;
        descriptionText.setPosition(xCor, yCor);
        descriptionText.setFillColor(Color::White);
        window.draw(descriptionText);

        //drawing category
        Text categoryText("Category: " + getCategory(), font, 20);
        yCor += 25;
        categoryText.setPosition(xCor, yCor);
        categoryText.setFillColor(Color::White);
        window.draw(categoryText);

        //drawing creation date
        Text creationDateText("Creation Date: " + getCreationDate(), font, 20);
        yCor += 25;
        creationDateText.setPosition(xCor, yCor);
        creationDateText.setFillColor(Color::White);
        window.draw(creationDateText);

        //drawing last modified date
        Text lastModifiedDateText("Last Modified Date: " + getLastModifiedDate(), font, 20);
        yCor += 25;
        lastModifiedDateText.setPosition(xCor, yCor);
        lastModifiedDateText.setFillColor(Color::White);
        window.draw(lastModifiedDateText);

        //drawing priority
        Text priorityText("Task Priority: " + getPriorityLabel(), font, 20);
        yCor += 25;
        priorityText.setPosition(xCor, yCor);
        priorityText.setFillColor(Color::White);
        window.draw(priorityText);

        //drawing due date
        Text dueDateText("Due Date: " + getDueDate(), font, 20);
        yCor += 25;
        dueDateText.setPosition(xCor, yCor);
        dueDateText.setFillColor(Color::White);
        window.draw(dueDateText);
    }

};

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




int main() {
    RenderWindow window(VideoMode(800, 600), "ProHassan");
    Font font;

    if (!font.loadFromFile("fonts/Roboto-Medium.ttf")) {
        return -1;
    }
    Menu menu(window);
    menu.display();

    return 0;
}