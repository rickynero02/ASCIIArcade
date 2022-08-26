#pragma once
#include <ncurses.h>

class Menu {

private:
    int maxX, maxY;
    WINDOW *menuwin;
    int highlight;

    const char* choices[3] = {
        "Play", 
        "Instructions", 
        "Credits"
    };

    void printBanner();
    void printMenu();

public:
    Menu();
    int show();
    ~Menu();
};