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
        mvprintw(0, 15, "%3d", map_pos);
        refresh();

        ch = wgetch(current_win);
        if ((ch % A_CHARTEXT) == 'q') {
            current_map->clearAll();
            run();
            break;
        }

        current_map->updateState(ch, tick);

        if (player->isDead) {
            showGameOver();
            break;
        }

        if (player->loadNextMap) {
            generateNewMap();
        }

        if (player->loadPreviousMap && map_pos > 0) {
            generatePreviousMap();
        } else {
            player->loadPreviousMap = false;
        }

        tick = (tick % 15) + 1;
        napms(15);
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

void Game::showGameOver() {
    clear();
    refresh();

    mvprintw(1, 1, "Premi ENTER per tornare al menu");

    attron(COLOR_PAIR(1));
    mvprintw(5, 1, "             GGGGGGGGGGGGG               AAA               MMMMMMMM               MMMMMMMMEEEEEEEEEEEEEEEEEEEEEE");
    mvprintw(6, 1, "          GGG::::::::::::G              A:::A              M:::::::M             M:::::::ME::::::::::::::::::::E");
    mvprintw(7, 1, "        GG:::::::::::::::G             A:::::A             M::::::::M           M::::::::ME::::::::::::::::::::E");
    mvprintw(8, 1, "       G:::::GGGGGGGG::::G            A:::::::A            M:::::::::M         M:::::::::MEE::::::EEEEEEEEE::::E");
    mvprintw(9, 1, "      G:::::G       GGGGGG           A:::::::::A           M::::::::::M       M::::::::::M  E:::::E       EEEEEE");
    mvprintw(10, 1, "     G:::::G                        A:::::A:::::A          M:::::::::::M     M:::::::::::M  E:::::E");
    mvprintw(11, 1, "     G:::::G                       A:::::A A:::::A         M:::::::M::::M   M::::M:::::::M  E::::::EEEEEEEEEE");
    mvprintw(12, 1, "     G:::::G    GGGGGGGGGG        A:::::A   A:::::A        M::::::M M::::M M::::M M::::::M  E:::::::::::::::E");
    mvprintw(13, 1, "     G:::::G    G::::::::G       A:::::A     A:::::A       M::::::M  M::::M::::M  M::::::M  E:::::::::::::::E");
    mvprintw(14, 1, "     G:::::G    GGGGG::::G      A:::::AAAAAAAAA:::::A      M::::::M   M:::::::M   M::::::M  E::::::EEEEEEEEEE");
    mvprintw(15, 1, "     G:::::G        G::::G     A:::::::::::::::::::::A     M::::::M    M:::::M    M::::::M  E:::::E");
    mvprintw(16, 1, "      G:::::G       G::::G    A:::::AAAAAAAAAAAAA:::::A    M::::::M     MMMMM     M::::::M  E:::::E       EEEEEE");
    mvprintw(17, 1, "       G:::::GGGGGGGG::::G   A:::::A             A:::::A   M::::::M               M::::::MEE::::::EEEEEEEE:::::E");
    mvprintw(18, 1, "        GG:::::::::::::::G  A:::::A               A:::::A  M::::::M               M::::::ME::::::::::::::::::::E");
    mvprintw(19, 1, "          GGG::::::GGG:::G A:::::A                 A:::::A M::::::M               M::::::ME::::::::::::::::::::E");
    mvprintw(20, 1, "             GGGGGG   GGGGAAAAAAA                   AAAAAAAMMMMMMMM               MMMMMMMMEEEEEEEEEEEEEEEEEEEEEE");

    mvprintw(22, 50, "          OOOOOOOOO     VVVVVVVV           VVVVVVVVEEEEEEEEEEEEEEEEEEEEEERRRRRRRRRRRRRRRRR");
    mvprintw(23, 50, "        OO:::::::::OO   V::::::V           V::::::VE::::::::::::::::::::ER::::::::::::::::R");
    mvprintw(24, 50, "      OO:::::::::::::OO V::::::V           V::::::VE::::::::::::::::::::ER::::::RRRRRR:::::R");
    mvprintw(25, 50, "     O:::::::OOO:::::::OV::::::V           V::::::VEE::::::EEEEEEEEE::::ERR:::::R     R:::::R");
    mvprintw(26, 50, "     O::::::O   O::::::O V:::::V           V:::::V   E:::::E       EEEEEE  R::::R     R:::::R");
    mvprintw(27, 50, "     O:::::O     O:::::O  V:::::V         V:::::V    E:::::E               R::::R     R:::::R");
    mvprintw(28, 50, "     O:::::O     O:::::O   V:::::V       V:::::V     E::::::EEEEEEEEEE     R::::RRRRRR:::::R");
    mvprintw(29, 50, "     O:::::O     O:::::O    V:::::V     V:::::V      E:::::::::::::::E     R:::::::::::::RR");
    mvprintw(30, 50, "     O:::::O     O:::::O     V:::::V   V:::::V       E:::::::::::::::E     R::::RRRRRR:::::R");
    mvprintw(31, 50, "     O:::::O     O:::::O      V:::::V V:::::V        E::::::EEEEEEEEEE     R::::R     R:::::R");
    mvprintw(32, 50, "     O:::::O     O:::::O       V:::::V:::::V         E:::::E               R::::R     R:::::R");
    mvprintw(33, 50, "     O::::::O   O::::::O        V:::::::::V          E:::::E       EEEEEE  R::::R     R:::::R");
    mvprintw(34, 50, "     O:::::::OOO:::::::O         V:::::::V         EE::::::EEEEEEEE:::::ERR:::::R     R:::::R");
    mvprintw(35, 50, "      OO:::::::::::::OO           V:::::V          E::::::::::::::::::::ER::::::R     R:::::R");
    mvprintw(36, 50, "        OO:::::::::OO              V:::V           E::::::::::::::::::::ER::::::R     R:::::R");
    mvprintw(37, 50, "          OOOOOOOOO                 VVV            EEEEEEEEEEEEEEEEEEEEEERRRRRRRR     RRRRRRR");
    attron(COLOR_PAIR(1));

    int ch;
    while((ch = getch()) != 10) {}
    run();
}