#pragma once

#include <vector>
#include <memory>

class Object;
class Player;
class ActiveEntity;

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
    void setPlayer(std::shared_ptr<Player> p) { player = p; }
    std::shared_ptr<ActiveEntity> getEntity(int, int, char);
};