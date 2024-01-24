#ifndef MENU_H
#define MENU_H

#include "task.h"
#include "appointment.h"

//The menu class manages the whole system
//It basically controls the systems basic functionality
//allowing the user to add tasks, notes and appointments and display them
class Menu {
private:
    RenderWindow& window;
    Text options[7];
    Font font;
    Sprite background;
    Texture bgTexture;
    vector<Task> tasks;
    vector<Appointment> appointments;
    int xCor;
    int yCor;

    //helper functions
    void handleKeyPress(Keyboard::Key key, RenderWindow& window, vector<Task>& tasks, vector<Appointment>& appointments) {
        switch (key) {
        case Keyboard::Num1:
        case Keyboard::Numpad1:
            cout << "Displaying tasks...\n";
            displayTasksScreen(window, tasks);
            break;
        case Keyboard::Num2:
        case Keyboard::Numpad2:
            cout << "Adding tasks...\n";
            addTaskScreen(window, tasks);
            break;
        case Keyboard::Num3:
        case Keyboard::Numpad3:
            cout << "Displaying appointments...\n";
            displayAppointmentsScreen(window, appointments);
            break;
        case Keyboard::Num4:
        case Keyboard::Numpad4:
            cout << "Adding..." << endl;
            addAppointmentScreen(window, appointments);
            break;
        case Keyboard::Num5:
        case Keyboard::Numpad5:

            window.close();
            break;

        default:
            break;
        }
    }

    void inputText(RenderWindow& window, Font& font, Text& pageTitle, Text& promptText, float& x, float& y, string& value) {
        Text inputText("", font, 24);
        inputText.setFillColor(Color::White);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                else if (event.type == Event::TextEntered) {
                    if (event.text.unicode == 13) {  // Enter key
                        value = inputText.getString().toAnsiString();
                        return;
                    }
                    else if (event.text.unicode == 8) {  // Backspace key
                        // Handle backspace
                        if (!inputText.getString().isEmpty()) {
                            string str = inputText.getString();
                            str.pop_back();
                            inputText.setString(str);
                        }
                    }
                    else {
                        // Handle other key presses
                        inputText.setString(inputText.getString() + static_cast<char>(event.text.unicode));
                    }
                }
            }

            window.clear();
            window.draw(background);
            window.draw(pageTitle);
            window.draw(promptText);
            inputText.setPosition(x, y + 30);
            window.draw(inputText);
            window.display();
        }
    }

    template <typename T>
    void inputNumber(RenderWindow& window, Font& font, Text& pageTitle, Text& promptText, float& x, float& y, T& object, void (T::* setter)(int)) {
        Text inputText("", font, 24);
        inputText.setFillColor(Color::White);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                else if (event.type == Event::TextEntered) {
                    if (event.text.unicode == 13) {  // Enter key
                        (object.*setter)(stoi(inputText.getString().toAnsiString()));
                        return;
                    }
                    else if (event.text.unicode == 8) {  // Backspace key
                        // Handle backspace
                        if (!inputText.getString().isEmpty()) {
                            string str = inputText.getString();
                            str.pop_back();
                            inputText.setString(str);
                        }
                    }
                    else {
                        // Handle other key presses
                        inputText.setString(inputText.getString() + static_cast<char>(event.text.unicode));
                    }
                }
            }

            window.clear();
            window.draw(background);
            window.draw(pageTitle);
            window.draw(promptText);
            inputText.setPosition(x, y + 30);
            window.draw(inputText);
            window.display();
        }
    }

    template <typename T>
    void inputBool(RenderWindow& window, Font& font, Text& pageTitle, Text& promptText, float& x, float& y, T& object, void (T::* setter)()) {
        Text inputText("", font, 24);
        inputText.setFillColor(Color::White);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                else if (event.type == Event::TextEntered) {
                    if (event.text.unicode == '0' || event.text.unicode == '1') {
                        (object.*setter)();
                        return;
                    }
                }
            }

            window.clear();
            window.draw(background);
            window.draw(pageTitle);
            window.draw(promptText);
            inputText.setPosition(x, y + 30);
            window.draw(inputText);
            window.display();
        }
    }



public:
    Menu(RenderWindow& window) : window(window) {
        //loading font and background texture
        if (!font.loadFromFile("fonts/Roboto-Medium.ttf")) {
            cerr << "Error loading font." << endl;
        }
        bgTexture.loadFromFile("img/background.png");
        background.setTexture(bgTexture);
        background.setScale(1, 2);

        //initializing tasks
        Task task1("Task 1", "Complete assignment", "Study", 1, "2024-01-15", false);
        Task task2("Task 2", "Prepare presentation", "Work", 2, "2024-01-20", false);
        tasks = { task1, task2 };

        //initializing notes
        Appointment appointment1("Meeting 1", "Team meeting", "Work", "2024-01-15 09:00:00", "2024-01-15 10:30:00", "Office", { "John", "Jane" });
        appointment1.setReminder("2024-01-14 15:00:00");  // Set a reminder for 1 day before
        Appointment appointment2("Meeting 2", "Client meeting", "Work", "2024-01-20 14:00:00", "2024-01-20 15:30:00", "Client Office", { "ClientA", "ClientB" });
        appointment2.setReminder("2024-01-19 10:00:00");  // Set a reminder for 1 day before
        appointments = { appointment1, appointment2 };

        //initializing menu options
        options[0].setString("1. Display Tasks");
        options[1].setString("2. Add Tasks");
        options[2].setString("3. Display Appointments");
        options[3].setString("4. Add Appointments");
        options[4].setString("5. Exit");

        for (auto& option : options) {
            option.setFont(font);
            option.setCharacterSize(30);
            option.setFillColor(Color::White);
        }

        options[0].setPosition(270, 170);
        options[1].setPosition(270, 220);
        options[2].setPosition(270, 270);
        options[3].setPosition(270, 320);
        options[4].setPosition(270, 370);


        window.setTitle("PlannerHassan");
        xCor = 20;
        yCor = 60;
    }

    void display() {
        //setting page title
        Text pageTitle;
        pageTitle.setString("PlannerHassan");
        pageTitle.setFont(font);
        pageTitle.setCharacterSize(60);
        pageTitle.setFillColor(Color::White);
        pageTitle.setPosition(250, 30);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                if (event.type == Event::KeyPressed) {
                    //handling menu choices
                    handleKeyPress(event.key.code, window, tasks, appointments);
                }
            }

            window.clear();
            window.draw(background);
            window.draw(pageTitle);

            for (const auto& option : options) {
                window.draw(option);
            }

            window.display();
        }
    }

    //In-order Code

    //task functions
    void displayTasksScreen(RenderWindow& window, vector<Task>& tasks) {
        window.clear();
        xCor = 20;
        yCor = 100;

        //setting background elements
        Text pageTitle;
        pageTitle.setString("Tasks");
        pageTitle.setFont(font);
        pageTitle.setCharacterSize(60);
        pageTitle.setFillColor(Color::White);
        pageTitle.setPosition(300, 30);

        Text key1;
        key1.setString("Next Page [n]");
        key1.setFont(font);
        key1.setCharacterSize(16);
        key1.setFillColor(Color::White);
        key1.setPosition(700, 520);

        Text key2;
        key2.setString(" Prev Page [p]");
        key2.setFont(font);
        key2.setCharacterSize(16);
        key2.setFillColor(Color::White);
        key2.setPosition(700, 550);

        Text key3;
        key3.setString("Main Menu [esc]");
        key3.setFont(font);
        key3.setCharacterSize(16);
        key3.setFillColor(Color::White);
        key3.setPosition(680, 580);

        size_t startIndex = 0;  //index of the first task
        size_t endIndex = min(startIndex + 2, tasks.size());  //index of the last task

        while (window.isOpen()) {
            //drawing elements on screen
            window.draw(background);
            window.draw(pageTitle);
            window.draw(key1);
            window.draw(key2);
            window.draw(key3);

            //display tasks
            for (size_t i = startIndex; i < endIndex; ++i) {
                tasks[i].display(window, background, xCor, yCor);
                yCor += 25;  //add a line break
            }

            window.display();
            Event event;
            while (window.waitEvent(event)) {
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Escape) {
                        return;  //return to main menu
                    }
                    else if (event.key.code == Keyboard::N) {
                        //move to the next page and also reset yCor
                        startIndex += 2;
                        endIndex = min(startIndex + 2, tasks.size());
                        window.clear();
                        yCor = 100;
                        break;
                    }
                    else if (event.key.code == Keyboard::P && startIndex >= 2) {
                        //move to the previous page and also reset yCor
                        startIndex -= 2;
                        endIndex = min(startIndex + 2, tasks.size());
                        window.clear();
                        yCor = 100;
                        break;
                    }
                }
                else if (event.type == Event::Closed) {
                    window.close();
                    return;
                }
            }

        }
    }

    void addTaskScreen(RenderWindow& window, vector<Task>& tasks) {
        //create new task
        Task newTask;

        //drawing background elements
        window.draw(background);
        Text pageTitle;
        pageTitle.setString("Add Task");
        pageTitle.setFont(font);
        pageTitle.setCharacterSize(60);
        pageTitle.setFillColor(Color::White);
        pageTitle.setPosition(250, 30);
        window.draw(pageTitle);

        Text promptText;
        promptText.setFont(font);
        promptText.setCharacterSize(30);
        promptText.setFillColor(Color::White);
        promptText.setPosition(0, 100);
        float x = 20.0f;
        float y = 110.0f;

        //get user input for task details
        string value;
        promptText.setString("Enter new title: ");
        inputText(window, font, pageTitle, promptText, x, y, newTask.getTitle());

        promptText.setString("Enter new description: ");
        inputText(window, font, pageTitle, promptText, x, y, newTask.getDescription());

        promptText.setString("Enter new category: ");
        inputText(window, font, pageTitle, promptText, x, y, newTask.getCategory());

        newTask.setCreationDate();
        newTask.setLastModifiedDate();

        promptText.setString("Enter new priority (0-Low, 1-Medium, 2-High): ");
        inputNumber<Task>(window, font, pageTitle, promptText, x, y, newTask, &PriorityFeature::setPriority);

        promptText.setString("Enter new due date: ");
        inputText(window, font, pageTitle, promptText, x, y, value);
        newTask.setDueDate(value);

        promptText.setString("Enter completion status (0 or 1): ");
        inputBool(window, font, pageTitle, promptText, x, y, newTask, &Task::setCompleteTask);

        //add new task to the tasks vector
        tasks.push_back(newTask);
    }

    //appointment functions
    void displayAppointmentsScreen(RenderWindow& window, vector<Appointment>& appointments) {
        window.clear();
        xCor = 20;
        yCor = 120;

        //setting background elements
        Text pageTitle;
        pageTitle.setString("Appointments");
        pageTitle.setFont(font);
        pageTitle.setCharacterSize(60);
        pageTitle.setFillColor(Color::White);
        pageTitle.setPosition(180, 30);

        Text key1;
        key1.setString("Next Page [n]");
        key1.setFont(font);
        key1.setCharacterSize(16);
        key1.setFillColor(Color::White);
        key1.setPosition(700, 520);

        Text key2;
        key2.setString(" Prev Page [p]");
        key2.setFont(font);
        key2.setCharacterSize(16);
        key2.setFillColor(Color::White);
        key2.setPosition(700, 550);

        Text key3;
        key3.setString("Main Menu [esc]");
        key3.setFont(font);
        key3.setCharacterSize(16);
        key3.setFillColor(Color::White);
        key3.setPosition(680, 580);

        size_t startIndex = 0;  //index of the first appointment
        size_t endIndex = min(startIndex + 2, appointments.size());  //index of the last appointment

        while (window.isOpen()) {
            window.draw(background);
            window.draw(pageTitle);
            window.draw(key1);
            window.draw(key2);
            window.draw(key3);

            //display appointments
            for (size_t i = startIndex; i < endIndex; ++i) {
                appointments[i].display(window, background, xCor, yCor);
                yCor += 20;  //add a line break
            }

            window.display();
            Event event;
            while (window.waitEvent(event)) {
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::N) {
                        //move to the next page and reset yCor
                        startIndex += 2;
                        endIndex = min(startIndex + 2, appointments.size());
                        window.clear();
                        yCor = 120;
                        break;
                    }
                    else if (event.key.code == Keyboard::P && startIndex >= 2) {
                        //move to the previous page and reset yCor
                        startIndex -= 2;
                        endIndex = min(startIndex + 2, appointments.size());
                        window.clear();
                        yCor = 120;
                        break;
                    }
                    else if (event.key.code == Keyboard::Escape) {
                        return;  //return to main menu
                    }
                }
                else if (event.type == Event::Closed) {
                    window.close();
                    return;
                }
            }
        }
    }

    void addAppointmentScreen(RenderWindow& window, vector<Appointment>& appointments) {
        //create new appointment
        Appointment newAppointment;
        window.draw(background);

        //drawing background elements
        Text pageTitle;
        pageTitle.setString("Add Appointment");
        pageTitle.setFont(font);
        pageTitle.setCharacterSize(60);
        pageTitle.setFillColor(Color::White);
        pageTitle.setPosition(120, 30);
        window.draw(pageTitle);

        Text promptText;
        promptText.setFont(font);
        promptText.setCharacterSize(24);
        promptText.setFillColor(Color::White);
        promptText.setPosition(0, 110);
        float x = 20.0f;
        float y = 120.0f;

        //get user input for appointment details to store
        string title;
        promptText.setString("Enter new title: ");
        inputText(window, font, pageTitle, promptText, x, y, title);
        newAppointment.setTitle(title);

        string description;
        promptText.setString("Enter new description: ");
        inputText(window, font, pageTitle, promptText, x, y, description);
        newAppointment.setDescription(description);

        string category;
        promptText.setString("Enter new category: ");
        inputText(window, font, pageTitle, promptText, x, y, category);
        newAppointment.setCategory(category);

        newAppointment.setCreationDate();
        newAppointment.setLastModifiedDate();

        string startTime;
        promptText.setString("Enter start time: ");
        inputText(window, font, pageTitle, promptText, x, y, startTime);
        newAppointment.setStartAndEndTime(startTime);

        string endTime;
        promptText.setString("Enter end time: ");
        inputText(window, font, pageTitle, promptText, x, y, endTime);
        newAppointment.setStartAndEndTime(newAppointment.getStartTime(), endTime);

        string location;
        promptText.setString("Enter location: ");
        inputText(window, font, pageTitle, promptText, x, y, location);
        newAppointment.setLocation(location);

        string attendeesInput;
        promptText.setString("Enter attendees (comma-separated): ");
        inputText(window, font, pageTitle, promptText, x, y, attendeesInput);
        newAppointment.updatingAttendees(attendeesInput);

        string reminder;
        promptText.setString("Enter reminder: ");
        inputText(window, font, pageTitle, promptText, x, y, reminder);
        newAppointment.setReminder(reminder);

        //add new appointment to appointments vector
        appointments.push_back(newAppointment);
    }


};

#endif