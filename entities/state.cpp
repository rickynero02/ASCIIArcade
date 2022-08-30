#include "state.hpp"
#include "entity.hpp"
#include <algorithm>

void State::add(std::shared_ptr<Object> entity) {
    entities.push_back(entity);
}

void State::updateAll(int t) {
    for (std::shared_ptr<Object>& entity : entities) {
        entity->update(this, t);
    }
}

void State::drawAll() {
    for (std::shared_ptr<Object>& entity : entities) {
        entity->draw();
    }
    clear();
}

void State::clear() {
    std::erase_if(entities, [](std::shared_ptr<Object> entity) {
        return entity->getIcon() == ' ';
    });
}