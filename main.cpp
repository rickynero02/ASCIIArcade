#include "maps/map.hpp"

int main() { 
    initscr();
    cbreak();
    noecho();

    refresh();
    Map m;

    getch();
    endwin();
}