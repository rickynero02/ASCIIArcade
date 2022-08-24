#pragma once

typedef struct _position {
    int x, y;
} Position;

class Object {
protected:
    Position position;
    char icon;

public:
    Position getPosition() { return position; }
    const char getIcon() { return icon; }
};