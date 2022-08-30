#pragma once
#include "../maps/map.hpp"

class Game {

private:
    Map* current_map;
    void play();

    void showCredits();
    void showInfo();

public:
    Game();
    ~Game();
    void run();

};