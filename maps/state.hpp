#pragma once
#include "../entities/player.hpp"

//Rappresenta lo stato della mappa
class State {

private:
    Player *player;
    WINDOW *win;

public:
    State();
    ~State();

    Player *getPlayer();
    void show();
};