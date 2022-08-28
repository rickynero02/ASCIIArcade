#pragma once
#include "../entities/player.hpp"

//Rappresenta lo stato della mappa
struct State {
    Player *player;

    ~State() {
        delete player;
    }
};