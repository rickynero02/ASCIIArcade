#pragma once
#include "../maps/map.hpp"
#include <memory>

class Game {

private:
    std::shared_ptr<Map> current_map;
    void play();

    void showCredits();
    void showInfo();

public:
    Game();
    ~Game();
    void run();
};