#pragma once
#include "raylib.h"

class RubiksCube {
public:
    RubiksCube();
    void Draw();

private:
    float cubieSize;
    float spacing;
};
