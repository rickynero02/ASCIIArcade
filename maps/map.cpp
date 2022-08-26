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

    bool b;


    if(s%2==0){
        b= true;
    }
    else{
        b= false;
    }


    if(b==true){        // OStacoli orizzontale Sinistra e Sopra   //13


    if(m<=13){          //evita incontri con mura verticali
        for(int i = 1; i <= 40; i++){
        mvwprintw(win, 16, i, "%c", '-');
    }
    }

    else{
        for(int i = 1; i <= 40; i++){
        mvwprintw(win, m, i, "%c", '-');          

        }
    }


    if(m<=11){                              //non va contro porta chiusa
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
    
    else{               // Ostacoli Orizzontale Destra e Orizzontale Sinistra ; Ostacolo QUADRATO ; ostacolo linea larga



        if(m+m2<=28){

        for(int i = 15; i <= 55; i++){     //sotto
        
        mvwprintw(win, 23, i, "%c", '-');
        } 

        for(int i = 7; i <= 22; i++){
        
        mvwprintw(win, i, 14, "%c", '|');
        }
        
        
        
        for(int i = 7; i <= 22; i++){
        
        mvwprintw(win, i, 56, "%c", '|');
        }  


        for(int i = 1; i <=13; i++){     //ostacolo lato sinistro quadrato 
        
        mvwprintw(win, 12, i, "%c", '-');
        } 





        for(int i = 15; i <= 55; i++){        //sopra
        
        mvwprintw(win, 6, i, "%c", '-');
        } 
        
    
    }

    else if(m-m2<0){                             //ostacolo linea larga orizzontale

        for(int i = 1; i <= 62; i++){     
        
        mvwprintw(win, 15, i, "%c", '-');
        } 

    }

    else if(m+m2>=38){                             //ostacolo linea larga verticale

        for(int i = 1; i <= 22; i++){     
        
        mvwprintw(win, i, 35, "%c", '|');
        } 

    }


    else{
        
        for(int i = 68; i >= 29; i--){
        mvwprintw(win, m, i, "%c", '-');
        }

        if(m==m2 or m==m2+1 or m==m2+2 or m==m2+3 or m==m2+4 or m==m2+5 or m==m2-1 or m==m2-2 or m==m2-3 or m==m2-4 or m==m2-5){
        for(int i = 1; i <= 40; i++){
        mvwprintw(win, 25, i, "%c", '-'); 
                }
        }
        
        else{

        for(int i = 1; i <= 40; i++){
        mvwprintw(win, m2, i, "%c", '-'); 
            }

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