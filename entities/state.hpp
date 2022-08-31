#pragma once

#include <vector>
#include <memory>

class Object;
class Player;

class State {

private:
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Object>> entities;
    void clear();

public:
    State(std::shared_ptr<Player> player) : player(player) {}
    void add(std::shared_ptr<Object> entity);
    void updateAll(int);
    void drawAll();

    int size() { return entities.size(); }
    std::shared_ptr<Player> getPlayer() { return player; }
};