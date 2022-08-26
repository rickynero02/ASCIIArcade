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
    int val = m.show();
    clear();
    refresh();

    if (val == 0) {
        current_map->show();
        getch();
    }

    delete current_map;
    current_map = nullptr;
}

Game::~Game() {
    if (current_map != nullptr) {
        delete current_map;
    }
    endwin();
}