#include "map.hpp"
#include <ctime>
#include <cstdlib>
#include <ncurses.h>

Map::Map() { 
    win = newwin(height, width, start_y, start_x);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    createWalls();
    createDoors();
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
            mvwprintw(win, k, i, "%c", '-');          
        }

        int n = rand()%25+25;
        k = (m <= 11) ? 60 : ((n <= 19) ? 23 : n);
        for(int i = 1; i <= 10; i++){
            mvwprintw(win, i, k, "%c", '|');
        }

    } else {               
        /* Ostacoli Orizzontale Destra e Orizzontale Sinistra ; 
            Ostacolo QUADRATO ; ostacolo linea larga*/
        if(m + m2 <=28){
            for(int i = 15; i <= 55; i++){     //sotto
                mvwprintw(win, 23, i, "%c", '-');
                mvwprintw(win, 6, i, "%c", '-');
            } 

            for(int i = 7; i <= 22; i++){
                mvwprintw(win, i, 14, "%c", '|');
                mvwprintw(win, i, 56, "%c", '|');
            }

            for(int i = 1; i <=13; i++){     //ostacolo lato sinistro quadrato 
                mvwprintw(win, 12, i, "%c", '-');
            } 
        }
        else if(m - m2 < 0){                             //ostacolo linea larga orizzontale
            for(int i = 1; i <= 62; i++){     
                mvwprintw(win, 15, i, "%c", '-');
            } 
        }
        else if(m + m2 >= 38){                             //ostacolo linea larga verticale
            for(int i = 1; i <= 22; i++){     
                mvwprintw(win, i, 35, "%c", '|');
            } 
        }
        else{ 
            for(int i = 68; i >= 29; i--){
                mvwprintw(win, m, i, "%c", '-');
            }
            int k = (abs(m - m2) < 5) ? 25 : m2;
            for(int i = 1; i <= 40; i++){
                mvwprintw(win, k, i, "%c", '-'); 
            }
        }
    }
}


void Map::createDoors() {
    mvwprintw(win, 0, 10, "XXXXXXXXX");                                        
    for(int i=10; i<=19; i++){
        mvwprintw(win, 29, i, " ");  
    }
}

Map::~Map() { 
    delwin(win);
}