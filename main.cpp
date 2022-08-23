#include <iostream>
#include "entities/player.hpp"

int main(int, char**) {
    initscr();
    
    Player p;
    printw("Health: %d", p.getHealth());
    refresh();

    getch();
    endwin();
}
