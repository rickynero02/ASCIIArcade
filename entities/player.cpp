#include <string>
#include <ncurses.h>
#include "player.hpp"

Player::Player(){   //aspetto giocatore
    max_health = 20;  //massima vita giocatore
    health = max_health;
    damage = 2;      //danno
    bullet_icon = '-';
    win = newwin(1,1,0,0);
    mvwprintw(win, 0, 0, "%s", icon);
    wrefresh(win);
}

Player::Player(int x, int y){     
    max_health = 20;  
    health = max_health;
    current_position.x = x;
    current_position.y = y;
}

void Player::updateHealth(int n){
    health = health+n;
    if(health > max_health){
        max_health = health;
    }
}

void Player::setHealth(int n){
    health = n;
}

int Player::getHealth(){
    return health;
}

void Player::setDamage(int n){
    damage = n;
}

int Player::getDamage(){
    return damage;
}

void Player::setBulletIcon(char n){
    bullet_icon = n;
}

char Player::getBulletIcon(){
    return bullet_icon;
}