#include "StatsPanel.h"
#include <math.h>

void DrawStatsPanel(float cameraRadius, Vector2 cameraAngle) {
    int sw       = GetScreenWidth();
    int panelW   = 230;
    int panelH   = 110;
    int panelX   = sw - panelW - 10;
    int panelY   = 10;
    int fps      = GetFPS();
    DrawRectangle(panelX, panelY, panelW, panelH, { 0, 0, 0, 160 });
    DrawRectangleLines(panelX, panelY, panelW, panelH, { 80, 80, 100, 200 });

    Color fpsColor = (fps >= 55) ? (Color){ 80, 220,  80, 255 }
                   : (fps >= 30) ? (Color){ 220, 180, 60, 255 }
                                 : (Color){ 220,  60, 60, 255 };
    DrawText(TextFormat("FPS: %d", fps),
             panelX + 10, panelY + 10, 18, fpsColor);

    Color statColor = { 180, 200, 255, 255 };
    DrawText(TextFormat("Zoom:  %.1f",  cameraRadius),
             panelX + 10, panelY + 34, 15, statColor);
    DrawText(TextFormat("Yaw:   %.1f deg", cameraAngle.x * (180.0f / PI)),
             panelX + 10, panelY + 56, 15, statColor);
    DrawText(TextFormat("Pitch: %.1f deg", cameraAngle.y * (180.0f / PI)),
             panelX + 10, panelY + 78, 15, statColor);
}
