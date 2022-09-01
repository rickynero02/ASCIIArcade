#pragma once
#include <ncurses.h>
#include <memory>

class State;
class Player;
class Info;

class Map {

private:
    const int height = 30;
    const int width = 70;
    const int start_y = 3;
    const int start_x = 12;

    int val_y1, val_x1, val_y2, val_x2; //artefatti
    int x, y, z;   //muri
    int val_Y1, val_Y2, val_X1, val_X2, casual_alt; // nemici


    WINDOW *win;
    std::shared_ptr<State> state;
    std::unique_ptr<Info> info;

    void createWalls();
    void createDoors();
    void createArtifact();
    void createBaseEnemy();
    void createBossEenemy();
    void createSingleArtifact(int, int);

public:
    Map(std::shared_ptr<Player>);
    ~Map();

    void show();
    WINDOW * getWindow();
    void updateState(int, int);
};