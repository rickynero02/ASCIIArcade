#include "entity.hpp"

void Entity::setHealth(int n){
    health = n;
}

int Entity::getHealth(){
    return health;
}

void Entity::setDamage(int n){
    damage = n;
}

int Entity::getDamage(){
    return damage;
}

void Entity::setBulletIcon(char n){
    bullet_icon = n;
}

char Entity::getBulletIcon(){
    return bullet_icon;
}