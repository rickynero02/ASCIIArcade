#include "game.hpp"
#include "menu.hpp"
#include <ncurses.h>
#include "../entities/player.hpp"
#include "../entities/state.hpp"
#include <memory>
#include "info.hpp"

Game::Game()
{
    initscr();
    noecho();
    curs_set(0);

    current_map = new Map();
}

void Game::run()
{
    initscr();

    Menu m;
    int val = m.show();
    clear();
    refresh();
    switch (val)
    {
    case 0:
        current_map->show();
        play();
        break;

    case 1:
        showInfo();
        break;

    case 2:
        showCredits();
        break;
    }

    delete current_map;
    current_map = nullptr;
}

void Game::play()
{
    WINDOW *w = current_map->getWindow();
    auto player = std::make_shared<Player>(w, 15, 28);
    auto state = std::make_unique<State>();

    int ch, tick = 1;
    Info infoBoard(player);
    infoBoard.updateInfo(state->size());

    while (1)
    {
        ch = wgetch(w);
        if ((ch % A_CHARTEXT) == 'q')
        {

            wclear(w);
            wrefresh(w);
            run();

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

Game::~Game()
{
    if (current_map != nullptr)
    {
        delete current_map;
    }
    endwin();
}

void Game::showCredits()
{
    initscr();

    WINDOW *w;

    while (wgetch(w) != 'q')
    {
        clear();

        int height = 30;
        int width = 110;
        int start_y = 3;
        int start_x = 12;

        refresh();

        if (!has_colors())
        {
            printw("IN SEGUITO AD UN CONTROLLO, \nSI E' VERIFICATO CHE IL SUO TERMINALE NON SOPPORTA I COLORI");

            getch();
            endwin();
        }

        start_color();

        refresh();

        init_pair(1, COLOR_BLUE, COLOR_BLACK);

        w = newwin(height, width, start_y, start_x);
        box(w, 0, 0);

        attron(COLOR_PAIR(1));
        mvwprintw(w, 3, 50, "ASCIIArcade GAME");
        mvwprintw(w, 4, 53, "2022-2023");
        mvwprintw(w, 10, 20, "Riccardo Nisidi");
        mvwprintw(w, 13, 20, "Bogdan Chirila");
        mvwprintw(w, 20, 20, "Progetto di Informatica I Anno Scolastico UNIBO");
        mvwprintw(w, 21, 20, "Alma Matter");
        mvwprintw(w, 22, 54, "Bologna");
        attroff(COLOR_PAIR(1));

        wrefresh(w);
    }

    wclear(w);
    wrefresh(w);
    run();
}

void Game::showInfo()
{

    initscr();

    WINDOW *w;

    while (wgetch(w) != 'q')
    {
        clear();

        int height = 30;
        int width = 110;
        int start_y = 3;
        int start_x = 12;

        refresh();

        if (!has_colors())
        {
            printw("IN SEGUITO AD UN CONTROLLO, \nSI E' VERIFICATO CHE IL SUO TERMINALE NON SOPPORTA I COLORI");

            getch();
            endwin();
        }

        start_color();

        refresh();

        init_pair(1, COLOR_BLUE, COLOR_BLACK);

        w = newwin(height, width, start_y, start_x);
        box(w, 0, 0);

        attron(COLOR_PAIR(1));
        mvwprintw(w, 5, 20, "TASTI FRECCIA -SU-GIU-DESTRA-SINISTRA- : SPOSTAMENTO DEL GIOCATORE");
        mvwprintw(w, 7, 20, "F : SPARA");
        mvwprintw(w, 9, 20, "Q : TORNA AL MENU");
        mvwprintw(w, 19, 20, "OBBIETTIVO : SUPERARE PIU LIVELLI POSSIBILI,");
        mvwprintw(w, 20, 20, "SCONFIGGI I NEMICI PER OTTENERE LE CHIAVI CHE TI PERMETTERANNO DI");
        mvwprintw(w, 21, 20, "APRIRE LE PORTE!");
        mvwprintw(w, 25, 50, "GOOD LUCK.");
        attroff(COLOR_PAIR(1));

        wrefresh(w);
    }

    wclear(w);
    wrefresh(w);
    run();
}