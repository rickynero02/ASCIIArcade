#include "game.hpp"
#include "menu.hpp"
#include <ncurses.h>
#include "../entities/player.hpp"
#include "../entities/state.hpp"
#include <memory>
#include "info.hpp"

Game::Game() {
    initscr();
    noecho();
    curs_set(0);

    current_map = new Map();
}

void Game::run() {
    Menu m;
    int val = m.show();
    clear();
    refresh();

    if (val == 0) {
        current_map->show();
        play();
    }
    delete current_map;
    current_map = nullptr;
}

void Game::play() {
    WINDOW *w = current_map->getWindow();
    auto player = std::make_shared<Player>(w, 15, 28);
    auto state = std::make_unique<State>();

    int ch, tick = 1;
    Info infoBoard(player);
    infoBoard.updateInfo(state->size());

    while(1) {
        ch = wgetch(w);
        if ((ch % A_CHARTEXT) == 'q') {
            break;
        }

        player->update(state.get(), ch);
        state->updateAll(tick);

        player->draw();
        state->drawAll();
        wrefresh(w);

        infoBoard.updateInfo(state->size());

        tick = (tick % 10) + 1;
        napms(10);
    }
}

Game::~Game() {
    if (current_map != nullptr) {
        delete current_map;
    }
    endwin();
}