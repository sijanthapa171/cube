#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "3D Cube in Raylib");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawCube(cubePosition, 4.0f, 4.0f, 4.0f, MAROON);
        DrawCubeWires(cubePosition, 4.0f, 4.0f, 4.0f, DARKGRAY);
        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawText("Raylib 3D Cube", 10, 10, 20, DARKGRAY);
        DrawText("Use Mouse to Move Camera", 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
