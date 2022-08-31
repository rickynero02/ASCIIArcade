#include "map.hpp"
#include <ctime>
#include <cstdlib>
#include <ncurses.h>

#include "../entities/player.hpp"
#include "../entities/state.hpp"
#include "../entities/artifact.hpp"
#include "info.hpp"

Map::Map(std::shared_ptr<Player> player)
{
    win = newwin(height, width, start_y, start_x);
    keypad(win, true);

    player->setWindow(win);
    state = std::make_shared<State>(player);
    info = std::make_unique<Info>(state);
    srand(time(NULL));

    n1 = rand() % 3 + 1; 
    n2 = 27;
    m1 = rand() % 2 + 21; 
    m2 = rand() % 62 + 6; 

    x = rand() % 10 + 11;
    y = rand() % 10 + 11;
    z = rand() % 2 + 10;

    createArtifact();
}

void Map::updateState(int ch, int tick) {
    auto p = state->getPlayer();
    p->update(state.get(), ch);
    state->updateAll(tick);

    p->draw();
    state->drawAll();
    wrefresh(win);
    info->updateInfo();
}

void Map::createArtifact()
{
    int Y, X;

    bool b = ((n1 + n2) % 2) == 0;
    b = ((m1 + m2) % 2) == 0;
    X = (b) ? m1 : m2;
    Y = (b) ? n1 : n2;

    auto a = std::make_shared<Artifact>(win, Y, X);
    auto r = std::make_shared<Artifact>(win, X, Y);

    state->add(a);
    state->add(r);
}

void Map::show()
{
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    createWalls();
    createDoors();
    wtimeout(win, 0);
    wrefresh(win);
}

void Map::createWalls()
{
    bool b = (z % 2 == 0);

    if (b)
    {       
        /* Ostacoli orizzontale Sinistra e Sopra
        evita incontri con mura verticali */
        int k = (x <= 13) ? 16 : x;
        for (int i = 1; i <= 40; i++) {
            mvwaddch(win, k, i, '-');
        }

        int n = rand() % 25 + 25;
        k = (x <= 11) ? 60 : ((n <= 19) ? 23 : n);
        for (int i = 1; i <= 10; i++) {
            mvwaddch(win, i, k, '|');
        }
    }
    else
    {
        /* Ostacoli Orizzontale Destra e Orizzontale Sinistra ;
            Ostacolo QUADRATO ; ostacolo linea larga*/
        if (x + y <= 28)
        {
            for (int i = 15; i <= 55; i++) {
                mvwaddch(win, 23, i, '-');
                mvwaddch(win, 6, i, '-');
            }

            for (int i = 7; i <= 22; i++) {
                mvwaddch(win, i, 14, '|');
                mvwaddch(win, i, 56, '|');
            }

            // ostacolo lato sinistro quadrato
            for (int i = 1; i <= 13; i++) { 
                mvwaddch(win, 12, i, '-');
            }
        }
        else if (x - y < 0)
        {
            // ostacolo linea larga orizzontale
            for (int i = 1; i <= 62; i++) {
                mvwaddch(win, 15, i, '-');
            }
        }
        else if (x + y >= 38)
        { 
            // ostacolo linea larga verticale
            for (int i = 1; i <= 22; i++) {
                mvwaddch(win, i, 35, '|');
            }
        }
        else
        {
            for (int i = 68; i >= 29; i--) {
                mvwaddch(win, x, i, '-');
            }
            int k = (abs(x - y) <= 5) ? 25 : y;
            for (int i = 1; i <= 40; i++) {
                mvwaddch(win, k, i, '-');
            }
        }
    }
}

void Map::createDoors()
{
    mvwprintw(win, 0, 10, "XXXXXXXXX");
    for (int i = 10; i <= 19; i++) {
        mvwaddch(win, 29, i, ' ');
    }
}

WINDOW *Map::getWindow() {
    return win;
}

Map::~Map() {
    delwin(win);
}