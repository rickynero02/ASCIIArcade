#pragma once

#include "../entities/player.hpp"

class Info {

private:
    std::shared_ptr<Player> player;
    WINDOW* win;

public:
    Info(std::shared_ptr<Player> player) : player(player) {
        win = newwin(8, 18, 25, 90);
        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    }

    ~Info() {
        delwin(win);
    }
    void updateInfo(int n);
};