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
    auto player = std::make_shared<Player>();

    current_map.reset();
    current_map = std::make_shared<Map>(player);
    current_map->show();

    WINDOW *w = current_map->getWindow();

    int ch, tick = 1;
    while (1)
    {
        ch = wgetch(w);
        if ((ch % A_CHARTEXT) == 'q') {
            wclear(w);
            wrefresh(w);
            run();
            break;
        }

        current_map->updateState(ch, tick);
        tick = (tick % 10) + 1;
        napms(10);
    }
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
        mvwprintw(w, 10, 20, "Riccardo Nisidi");
        mvwprintw(w, 13, 20, "Bogdan Chirila");
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
        mvwprintw(w, 9, 20, "PREMI UN TASTO QUALSIASI PER TORNARE AL MENU");
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