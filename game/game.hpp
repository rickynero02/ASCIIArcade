#pragma once
#include "../maps/map.hpp"
#include <memory>
#include <vector>

class Game {

private:
    std::shared_ptr<Map> current_map;
    std::shared_ptr<Player> player;

    void play();
    void showCredits();
    void showInfo();
    void showGameOver();
    
    void generateNewMap();
    void generatePreviousMap();

    int map_pos;
    int last_map_pos;
    WINDOW* current_win;
    std::vector<std::shared_ptr<Map>> map_list;

public:
    Game();
    ~Game();
    void run();
};