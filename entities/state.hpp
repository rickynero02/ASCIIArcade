#pragma once

#include <vector>
#include <memory>

class Object;

class State {

private:
    std::vector<std::shared_ptr<Object>> entities;
    void clear();

public:
    void add(std::shared_ptr<Object> entity);
    void updateAll(int);
    void drawAll();

    int size() { return entities.size(); }
};