#include "maps/map.hpp"

int main() { 
    initscr();
    cbreak();

    refresh();
    Map m;

    getch();
    endwin();
}