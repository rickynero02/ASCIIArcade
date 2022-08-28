#pragma once
#include "../maps/map.hpp"

class Game {

private:
    Map* current_map;
    void play();

public:
    Game();
    ~Game();
    void run();
};