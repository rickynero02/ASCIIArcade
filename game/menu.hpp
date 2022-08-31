#pragma once
#include <ncurses.h>

class Menu {

private:
    int maxX, maxY;
    WINDOW *menuwin;
    int highlight;

    const char* choices[4] = {
        "Play", 
        "Instructions", 
        "Credits", 
        "Quit"
    };

    void printBanner();
    void printMenu();

public:
    Menu();
    int show();
    ~Menu();
};