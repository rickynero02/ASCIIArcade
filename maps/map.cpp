#include "map.hpp"
#include <ctime>
#include <cstdlib>
#include <ncurses.h>

Map::Map() { 
    win = newwin(height, width, start_y, start_x);
    keypad(win, true);
}

void Map::show() {
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    createWalls();
    createDoors();
    wtimeout(win, 0);
    wrefresh(win);
}

void Map::createWalls() {
    srand(time(NULL));      

    int m = rand()%10+11;
    int m2 = rand()%10+11;
    int s = rand()%2+10;

    bool b = (s % 2 == 0);

    if(b){        // OStacoli orizzontale Sinistra e Sopra   //13
        int k = (m <= 13) ? 16 : m; //evita incontri con mura verticali
        for(int i = 1; i <= 40; i++) {
            mvwaddch(win, k, i, '-');          
        }

        int n = rand()%25+25;
        k = (m <= 11) ? 60 : ((n <= 19) ? 23 : n);
        for(int i = 1; i <= 10; i++){
            mvwaddch(win, i, k, '|');
        }

    } else {               
        /* Ostacoli Orizzontale Destra e Orizzontale Sinistra ; 
            Ostacolo QUADRATO ; ostacolo linea larga*/
        if(m + m2 <=28){
            for(int i = 15; i <= 55; i++){     //sotto
                mvwaddch(win, 23, i, '-');
                mvwaddch(win, 6, i, '-');
            } 

            for(int i = 7; i <= 22; i++){
                mvwaddch(win, i, 14, '|');
                mvwaddch(win, i, 56, '|');
            }

            for(int i = 1; i <=13; i++){     //ostacolo lato sinistro quadrato 
                mvwaddch(win, 12, i, '-');
            } 
        }
        else if(m - m2 < 0){                             //ostacolo linea larga orizzontale
            for(int i = 1; i <= 62; i++){     
                mvwaddch(win, 15, i, '-');
            } 
        }
        else if(m + m2 >= 38){                             //ostacolo linea larga verticale
            for(int i = 1; i <= 22; i++){     
                mvwaddch(win, i, 35, '|');
            } 
        }
        else{ 
            for(int i = 68; i >= 29; i--){
                mvwaddch(win, m, i, '-');
            }
            int k = (abs(m - m2) <= 5) ? 25 : m2;
            for(int i = 1; i <= 40; i++){
                mvwaddch(win, k, i, '-'); 
            }
        }
    }
}

void Map::createDoors() {
    mvwprintw(win, 0, 10, "XXXXXXXXX");                                        
    for(int i=10; i<=19; i++){
        mvwaddch(win, 29, i, ' ');  
    }
}

WINDOW* Map::getWindow() {
    return win;
}

Map::~Map() { 
    delwin(win);
}