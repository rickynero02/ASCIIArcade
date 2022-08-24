#include "entities/player.hpp"

int main(int, char**) {
    initscr();
    
    Player p(10, 11);
    printw("Health: %d", p.getHealth());
    refresh();

    getch();
    endwin();
}
