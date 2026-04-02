#pragma once
#include "raylib.h"

class RubiksCube {
public:
    RubiksCube();
    void Draw();

private:
    void DrawCubie(Vector3 position, float size, Color up, Color down, Color front, Color back, Color right, Color left);

    float cubieSize;
    float spacing;
};
