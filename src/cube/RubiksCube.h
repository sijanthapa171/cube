#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>

struct CubieState {
    Vector3 pos;
    Matrix transform;
    Color up, down, front, back, right, left;
};

class RubiksCube {
public:
    RubiksCube();
    void Update(float dt);
    void Draw();
    
    bool StartRotation(int axis, int slice, int direction);

    bool IsAnimating() const { return isAnimating; }

private:
    float cubieSize;
    float spacing;

    std::vector<CubieState> cubies;

    bool isAnimating;
    int animAxis;
    int animSlice;
    int animDir;
    float animAngle;
    float targetAngle;
};
