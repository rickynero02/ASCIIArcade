#include "map.hpp"
#include <ctime>
#include <cstdlib>
#include <ncurses.h>

#include "../entities/player.hpp"
#include "../entities/state.hpp"
#include "../entities/artifact.hpp"
#include "../entities/enemy.hpp"
#include "info.hpp"

Map::Map(std::shared_ptr<Player> player)
{
    win = newwin(height, width, start_y, start_x);
    keypad(win, true);

    player->setWindow(win);
    state = std::make_shared<State>(player);
    info = std::make_unique<Info>(state);
    srand(time(NULL));

    //per artefatti
    val_y1 = rand() % 3 + 2; 
    val_y2 = ((rand() % 2) == 0) ? 26 : 27;
    val_x1 = rand() % 11 + 2;
    val_x2 = rand() % 13 + 10;

    // per nemici
    val_Y1 = rand() % 5 + 1;
    val_Y2 = ((rand() % 2) == 0) ? 26 : 27;
    val_X1 = rand() % 11 + 2;
    val_X2 = rand() % 13 + 10;
    casual_alt = rand() % 7 + 1;

    //per ostacoli
    x = rand() % 10 + 11;
    y = rand() % 10 + 11;
    z = rand() % 2 + 10;

    createArtifact();
    createBaseEnemy();
    createBossEenemy();
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

void Map::createBossEenemy()
{
    int y, x;

    x = 69 - casual_alt;
    y = val_Y1;

    int posch = mvwinch(win, y, x);
    if (posch == ' ' && y < 30 && x < 70 && x > 0 && y > 0)
    {
        auto boss = std::make_shared<BossEnemy>(win, x, y, direction::xaxis, verse::negative);
        state->add(boss);
    }
}

void Map::createBaseEnemy()
{

    int y1, y2, x1, x2;

    bool q1 = ((y1 + x1) % 2) == 0;
    bool q2 = ((y2 + x2) % 2) == 0;

    x1 = (q1) ? val_X1 : val_X2;
    y1 = (q2) ? val_Y1 : val_Y2;

    y2 = (q2) ? val_Y2 : val_Y1;
    x2 = (q1) ? val_X2 : val_X1;

    if (y1 > 6)
    {
        x1 = 68 - casual_alt;
    }
    if (y2 > 6)
    {
        x2 = 68 - casual_alt;
    }

    int posch = mvwinch(win, y1, x1);
    if (posch == ' ' && y1 < 29 && x1 < 69 && x1 > 0 && y1 > 0)
    {
        auto n1 = std::make_shared<BaseEnemy>(win, x1, y1, direction::xaxis, verse::negative);
        state->add(n1);
    }

    int posch2 = mvwinch(win, y2, x2);
    if (posch2 == ' ' && y2 < 29 && x2 < 69 && x2 > 0 && y2 > 0)
    {
        auto n2 = std::make_shared<BaseEnemy>(win, x2, y2, direction::xaxis, verse::positive);
        state->add(n2);
    }
}

void Map::createArtifact()
{
    int Y, X, YY, XX;

    bool b = ((val_y1 + val_y2) % 2) == 0;
    bool t = ((val_x1 + val_x2) % 2) == 0;

    X = (b) ? val_x1 : val_x2;
    Y = (t) ? val_y1 : val_y2;

    YY= (t) ? val_y2 : val_y1;
    XX= (b) ? val_x2 : val_x1;

    createSingleArtifact(X, Y);
    createSingleArtifact(XX, YY);
}

void Map::createSingleArtifact(int X, int Y) {
    int posch = mvwinch(win, Y, X);
    if (posch == ' ' && Y < 28 && X < 68 && X > 1 && Y > 1)
    {
        buff bt = (rand() % 2 == 0) ? buff::health : buff::damage;
        buff_t m = (rand() % 2 == 0) ? buff_t::malus : buff_t::bonus;
        auto a = std::make_shared<Artifact>(win, X, Y, bt, m);
        state->add(a);
    }
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
    mvwprintw(win, 0, 10, "OOOOOOOOO");
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