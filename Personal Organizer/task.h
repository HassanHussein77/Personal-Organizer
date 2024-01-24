#ifndef TASK_H
#define TASK_H

#include "organizerItem.h"
#include "priorityFeature.h"

#include <iostream>

using namespace std;


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
#endif