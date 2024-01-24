#include "menu.h"

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