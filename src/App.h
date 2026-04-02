#pragma once

#include "raylib.h"
#include "RubiksCube.h"

class App {
public:
    App();
    void Init();
    void RunLoop();
    void Cleanup();

private:
    int screenWidth;
    int screenHeight;
    
    Camera3D camera;
    Vector2 cameraAngle;
    float cameraRadius;

    RubiksCube rubik;
};
