#ifndef ORGANIZERITEM_H
#define ORGANIZERITEM_H

#include "utility.h"
#include <SFML/Graphics.hpp>

using namespace sf;

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

#endif