#pragma once

#include "raylib.h"

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
    Vector3 cubePosition;
    Vector3 cubeSize;
    Vector2 cameraAngle;
    float cameraRadius;
};
