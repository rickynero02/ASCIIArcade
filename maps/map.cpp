#include "map.hpp"
#include <ctime>
#include <cstdlib>

Map::Map() { 
    win = newwin(height, width, start_y, start_x);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    createWalls();
    createDoors();
    wrefresh(win);
}

void Map::createWalls() {
    srand(time(NULL));      

    int m = rand()%20+10;
    for(int i = 1; i <= 50; i++){
        mvwprintw(win, m, i, "%c", '-');          
    }

    int n = rand()%60+10;
    for(int i = 1; i <= 15; i++){
        mvwprintw(win, i, n, "%c", '|');
    }
}

void Map::createDoors() {
    mvwprintw(win, 0, 10, "XXXXXXXXX");                                        
    //mvwprintw(win, 10, 0, "         ");    
}

Map::~Map() { 
    delwin(win);    //distruttore di memoria allocata 
}