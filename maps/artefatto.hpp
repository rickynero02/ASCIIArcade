// #include "../ASCIIArcade/entities/player.hpp"
#include <ncurses.h>

class Artefatto
{

private:
    
    int yLoc,xLoc;

    char icona;

    WINDOW * curwin;

    // int Aumenta_Danno();
    // int Aumenta_Salute();

public:

    Artefatto(WINDOW * win, int y, int x, char icon);
    
    void display();

    /*int Aumenta_Danno(){
        return player.damage= player.damage+5;
    }*/

    /*int Aumenta_Salute(){
        return player.life= player.life+5;
    }*/
};

    Artefatto::Artefatto(WINDOW * win, int y, int x, char icon){
        curwin=win;
        yLoc=y;
        xLoc=x;
        icona=icon;
        keypad(curwin, true);
    }

    void Artefatto::display(){
        mvwaddch(curwin,yLoc,xLoc,icona);

    }