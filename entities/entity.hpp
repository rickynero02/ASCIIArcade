#pragma once
#include "object.hpp"

class Entity : public Object {
    
protected:
    int damage; 
    int health; 
    char bullet_icon;

public:
    void setHealth(int set);    //imposta salute
    int getHealth();            //restituisce valore salute 

    void setDamage(int set);    //imposta danno
    int getDamage();            //restituisce valore danno

    void setBulletIcon(char set); //imposta aspetto proiettile
    char getBulletIcon();

    virtual void move(Position pos) = 0;
};