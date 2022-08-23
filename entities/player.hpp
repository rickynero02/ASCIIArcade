#pragma once
#include <ncurses.h>

typedef struct _position {
    int x, y;
} Position;

class Player{

protected:
    const char* icon = "P"; //aspetto giocatore
    char bullet_icon; //aspetto proiettile

    int health;       //vita giocatore
    int max_health;   //Massima vita giocatore
    int damage;       //Danno che fa il giocatore

    Position current_position;   //posizione giocatore
    WINDOW *win;      //finestra

public:
    Player();
    Player(int x, int y);
    void updateHearts();        //aumenta danno
    void updateHealth(int mod); //aumenta salute

    void setHealth(int set);    //imposta salute
    int getHealth();            //restituisce valore salute 

    void setDamage(int set);    //imposta danno
    int getDamage();            //restituisce valore danno

    void setBulletIcon(char set); //imposta aspetto proiettile
    char getBulletIcon();        

    void playerMove(int x, int y);
    Position getCurrentPosition();

    void handleInput(int input);
};