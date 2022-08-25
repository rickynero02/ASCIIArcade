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

    int m = rand()%10+11;
    for(int i = 1; i <= 40; i++){
        mvwprintw(win, m, i, "%c", '-');          
    }

    if(m<=11){
        for(int i = 1; i <= 10; i++){
        mvwprintw(win, i, 60, "%c", '|');
        }
    }

    else{
        int n = rand()%25+25;
        if(n<=19){
        for(int i = 1; i <= 10; i++){
        mvwprintw(win, i, 23, "%c", '|');
                } 
            }
        else{
                for(int i = 1; i <= 10; i++){
                mvwprintw(win, i, n, "%c", '|');
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
    delwin(win);    //distruttore di memoria allocata 
}