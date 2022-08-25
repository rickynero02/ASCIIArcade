#pragma once
#include "player.hpp"

class Artefact : public Object {

public:
    virtual void interactWithPlayer(Player& player) = 0;
};

class Key : public Artefact {

public:
    Key(int x, int y) {
        icon = 'K';
        position.x = x;
        position.y = y;
    }   

    void interactWithPlayer(Player& player) override {
        player.setHasKey(true);
    }
};

class Life : public Artefact {

public:
    Life(int x, int y) {
        icon = 'L';
        position.x = x;
        position.y = y;
    }

    void interactWithPlayer(Player& player) override {
        int h = player.getHealth();
        player.setHealth(h + 10);
    }
};

class Damage : public Artefact {

public:
    Damage(int x, int y) {
        icon = 'D';
        position.x = x;
        position.y = y;
    }

    void interactWithPlayer(Player& player) override {
        int d = player.getDamage();
        player.setDamage(d + 1);
    }
};