#include "game.hpp"
#include "menu.hpp"
#include <ncurses.h>

Game::Game() {
    initscr();
    cbreak();
    noecho();

    clear();
    refresh();

    current_map = new Map();
}

void Game::run() {
    Menu m;
    int val = m.show(); //Mosta il menu
    clear();
    refresh();

    if (val == 0) {
        //Se l'utente ha scelto play fa partire il gioco
        current_map->show();
        play();
    }
    delete current_map;
    current_map = nullptr;
}

void Game::play() {
    WINDOW* mapwin = current_map->getWindow();
    State* state = current_map->getState();
    Player* p = state->getPlayer();

    int ch;

    while (1) {
        ch = wgetch(mapwin);
        Position currpos = p->getPosition();  //Salvo la posizione corrente del player
        Position newpos = currpos;

        //Stampo un carattere vuoto nella sua posizione in modo
        //da eliminare il vecchio carattere
        mvwprintw(mapwin, currpos.y, currpos.x, "%c", ' ');
        wrefresh(mapwin);

        //Controllo dove deve andare il player
        switch (ch) {
            case 65:  //KEY_UP
                newpos.y--;
                break;
            case 66: //KEY_DOWN
                newpos.y++;
                break;
            case 67: //KEY_RIGHT
                newpos.x++;
                break;
            case 68:  //KEY_LEFT
                newpos.x--;
                break;
        }

        //Muovo il player nella posizione nuova
        p->move(mapwin, newpos);
        //Aggiorno lo stato
        current_map->updateState();
    }
}

Game::~Game() {
    if (current_map != nullptr) {
        delete current_map;
    }
    endwin();
}