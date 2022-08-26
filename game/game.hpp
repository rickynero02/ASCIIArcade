#pragma once
#include "../maps/map.hpp"

class Game {

private:
    Map* current_map;

public:
    Game();
    ~Game();
    void run();
};