#include "game.hpp"
#include "menu.hpp"
#include <ncurses.h>
#include "../entities/player.hpp"
#include "../entities/state.hpp"
#include <memory>

Game::Game()
{
    initscr();
    noecho();
    curs_set(0);

    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);

    map_pos = -1;
    last_map_pos = -1;
    map_list.reserve(10);
}

void Game::run()
{
    clear();
    refresh();

    Menu m;
    int val = m.show();

    clear();
    refresh();

    switch (val) {
    case 0:
        map_list.clear();
        map_pos = -1;
        last_map_pos = -1;

        player = std::make_shared<Player>();
        play();
        break;
    case 1:
        showInfo();
        break;
    case 2:
        showCredits();
        break;
    }
}

void Game::play()
{
    generateNewMap();

    int ch, tick = 1;
    while (1)
    {
        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "Current Level:");
        attroff(COLOR_PAIR(1));
        mvprintw(0, 20, "%3d", map_pos);
        refresh();

        ch = wgetch(current_win);
        if ((ch % A_CHARTEXT) == 'q') {
            current_map->clearAll();
            run();
            break;
        }

        current_map->updateState(ch, tick);

        if (player->loadNextMap) {
            generateNewMap();
        }

        if (player->loadPreviousMap && map_pos > 0) {
            generatePreviousMap();
        } else {
            player->loadPreviousMap = false;
        }

        tick = (tick % 10) + 1;
        napms(10);
    }
}

void Game::generateNewMap() {
    player->loadNextMap = false;
    if (current_map != nullptr) {
        current_map->clearAll();
    }

    bool isNew = last_map_pos == map_pos;
    if (isNew) {
        current_map = std::make_shared<Map>(player);
        map_pos++;
        last_map_pos++;
        map_list[map_pos] = current_map;
        player->setHasKey(false);
    } else {
        map_pos++;
        current_map = map_list[map_pos];
        current_map->resetStatePlayer(player);
        player->setHasKey(current_map->isCleared);
    } 

    current_win = current_map->getWindow();
    current_map->show();
}

void Game::generatePreviousMap() {
    current_map->clearAll();
    map_pos--;
    current_map = map_list[map_pos];
    current_win = current_map->getWindow();

    current_map->resetStatePlayer(player);
    player->setHasKey(true);
    current_map->show();
    player->loadPreviousMap = false;
}

Game::~Game()
{
    endwin();
}

void Game::showCredits()
{
    clear();
    refresh();

    int height = 30;
    int width = 110;
    int start_y = 3;
    int start_x = 12;

    WINDOW *w;
    w = newwin(height, width, start_y, start_x);
    box(w, 0, 0);

    if (!has_colors()) {
        printw("IN SEGUITO AD UN CONTROLLO, \nSI E' VERIFICATO CHE IL SUO TERMINALE NON SOPPORTA I COLORI");
    } else {
        
        wattron(w, COLOR_PAIR(1));
        mvwprintw(w, 3, 50, "ASCIIArcade GAME");
        mvwprintw(w, 4, 53, "2022-2023");
        mvwprintw(w, 5, 33, "PER TORNARE AL MENU DA QUESTA SCHERMATA PREMI ENTER");
        mvwprintw(w, 10, 20, "Riccardo Nisidi");
        mvwprintw(w, 13, 20, "Bogdan Chirila");
        mvwprintw(w, 16, 20, "Valerio Pio De Nicola");
        mvwprintw(w, 20, 20, "Progetto di Informatica I Anno Scolastico UNIBO");
        mvwprintw(w, 21, 20, "Alma Matter");
        mvwprintw(w, 22, 54, "Bologna");
        wattroff(w, COLOR_PAIR(1));
        
        wrefresh(w);
    }

    wgetch(w);
    wclear(w);
    wrefresh(w);

    delwin(w);
    run();
}

void Game::showInfo()
{
    clear();
    refresh();

    int height = 30;
    int width = 110;
    int start_y = 3;
    int start_x = 12;

    WINDOW *w;
    w = newwin(height, width, start_y, start_x);
    box(w, 0, 0);

    if (!has_colors()) {
        printw("IN SEGUITO AD UN CONTROLLO, \nSI E' VERIFICATO CHE IL SUO TERMINALE NON SOPPORTA I COLORI");
    } else {
        wattron(w, COLOR_PAIR(1));
        mvwprintw(w, 5, 20, "TASTI FRECCIA -SU-GIU-DESTRA-SINISTRA- : SPOSTAMENTO DEL GIOCATORE");
        mvwprintw(w, 7, 20, "F : SPARA");
        mvwprintw(w, 9, 20, "Q : TORNA AL MENU DURANTE IL GIOCO / INTERROMPI LA PARTITA");
        mvwprintw(w, 11, 20, "PER TORNARE AL MENU DA QUESTA SCHERMATA PREMI ENTER");
        mvwprintw(w, 19, 20, "OBBIETTIVO : SUPERARE PIU LIVELLI POSSIBILI,");
        mvwprintw(w, 20, 20, "SCONFIGGI I NEMICI PER OTTENERE LE CHIAVI CHE TI PERMETTERANNO DI");
        mvwprintw(w, 21, 20, "APRIRE LE PORTE!");
        mvwprintw(w, 25, 50, "GOOD LUCK.");
        wattroff(w, COLOR_PAIR(1));
        wrefresh(w);
    }

    wgetch(w);
    wclear(w);
    wrefresh(w);

    delwin(w);
    run();
}