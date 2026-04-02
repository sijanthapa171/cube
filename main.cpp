#include "raylib.h"
#include <math.h>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "3D Cube in Raylib - 360 View");

    Camera3D camera = { 0 };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    Vector3 cubeSize = { 4.0f, 4.0f, 4.0f };

    Vector2 cameraAngle = { 0.78f, 0.5f }; 
    float cameraRadius = 15.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        cameraRadius -= GetMouseWheelMove() * 1.5f;
        if (cameraRadius < 5.0f) cameraRadius = 5.0f;
        if (cameraRadius > 100.0f) cameraRadius = 100.0f;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 delta = GetMouseDelta();
            cameraAngle.x -= delta.x * 0.01f;
            cameraAngle.y += delta.y * 0.01f;
        }

        if (cameraAngle.y > 1.5f) cameraAngle.y = 1.5f;
        if (cameraAngle.y < -1.5f) cameraAngle.y = -1.5f;

        camera.position.x = sinf(cameraAngle.x) * cosf(cameraAngle.y) * cameraRadius;
        camera.position.y = sinf(cameraAngle.y) * cameraRadius;
        camera.position.z = cosf(cameraAngle.x) * cosf(cameraAngle.y) * cameraRadius;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, MAROON);
        DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, DARKGRAY);
        DrawGrid(20, 1.0f);

        EndMode3D();

        DrawText("3D Cube", 10, 10, 20, DARKGRAY);
        DrawText("- Left Click + Drag to view 360 degrees around the cube", 10, 40, 20, DARKGRAY);
        DrawText("- Mouse Wheel to zoom in and out", 10, 60, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
