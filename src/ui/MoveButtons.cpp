#include "ui/MoveButtons.h"
#include <cstring>

struct ButtonDef {
    const char* label;
    const char* move;
};

struct ButtonGroup {
    const char* title;
    Color titleColor;
    ButtonDef buttons[18];
    int count;
};

static bool DrawButton(Rectangle rect, const char* label, bool enabled) {
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, rect) && enabled;
    bool clicked = hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    Color bg;
    if (!enabled)    bg = { 40, 40, 50, 180 };
    else if (hover)  bg = { 80, 90, 130, 230 };
    else             bg = { 50, 55, 75, 210 };

    DrawRectangleRec(rect, bg);
    DrawRectangleLinesEx(rect, 1.0f, hover ? (Color){140, 160, 255, 200} : (Color){70, 75, 95, 180});

    int fontSize = 14;
    int textW = MeasureText(label, fontSize);
    int tx = rect.x + (rect.width - textW) / 2;
    int ty = rect.y + (rect.height - fontSize) / 2;
    Color textColor = enabled ? (Color){230, 235, 255, 255} : (Color){100, 100, 120, 180};
    DrawText(label, tx, ty, fontSize, textColor);

    return clicked;
}

void DrawMoveButtons(RubiksCube& cube) {
    bool enabled = !cube.IsBusy();

    int panelX = 10;
    int panelY = 110;
    int panelW = 240;
    int btnW = 52;
    int btnH = 28;
    int padX = 6;
    int padY = 4;
    int cols = 3;

    ButtonGroup groups[] = {
        {
            "Face Moves", { 100, 200, 255, 255 },
            {
                {"R", "R"}, {"R'", "R'"}, {"R2", "R2"},
                {"L", "L"}, {"L'", "L'"}, {"L2", "L2"},
                {"U", "U"}, {"U'", "U'"}, {"U2", "U2"},
                {"D", "D"}, {"D'", "D'"}, {"D2", "D2"},
                {"F", "F"}, {"F'", "F'"}, {"F2", "F2"},
                {"B", "B"}, {"B'", "B'"}, {"B2", "B2"},
            },
            18
        },
        {
            "Middle Layers", { 255, 200, 100, 255 },
            {
                {"M", "M"}, {"M'", "M'"}, {"M2", "M2"},
                {"E", "E"}, {"E'", "E'"}, {"E2", "E2"},
                {"S", "S"}, {"S'", "S'"}, {"S2", "S2"},
            },
            9
        },
        {
            "Cube Rotations", { 100, 255, 180, 255 },
            {
                {"x", "x"}, {"x'", "x'"}, {"x2", "x2"},
                {"y", "y"}, {"y'", "y'"}, {"y2", "y2"},
                {"z", "z"}, {"z'", "z'"}, {"z2", "z2"},
            },
            9
        },
        {
            "Wide Moves", { 255, 140, 200, 255 },
            {
                {"r", "r"}, {"r'", "r'"}, {"r2", "r2"},
                {"u", "u"}, {"u'", "u'"}, {"u2", "u2"},
                {"f", "f"}, {"f'", "f'"}, {"f2", "f2"},
            },
            9
        },
    };
    int numGroups = 4;

    int totalH = 8;
    for (int g = 0; g < numGroups; g++) {
        totalH += 22;
        int rows = (groups[g].count + cols - 1) / cols;
        totalH += rows * (btnH + padY);
        totalH += 8;
    }

    DrawRectangle(panelX, panelY, panelW, totalH, { 15, 15, 25, 200 });
    DrawRectangleLines(panelX, panelY, panelW, totalH, { 60, 65, 90, 180 });

    int curY = panelY + 8;

    for (int g = 0; g < numGroups; g++) {
        DrawText(groups[g].title, panelX + 10, curY, 15, groups[g].titleColor);
        curY += 22;

        int startX = panelX + (panelW - (cols * btnW + (cols - 1) * padX)) / 2;

        for (int i = 0; i < groups[g].count; i++) {
            int col = i % cols;
            int row = i / cols;
            Rectangle rect = {
                (float)(startX + col * (btnW + padX)),
                (float)(curY + row * (btnH + padY)),
                (float)btnW,
                (float)btnH
            };

            if (DrawButton(rect, groups[g].buttons[i].label, enabled)) {
                cube.ExecuteMove(groups[g].buttons[i].move);
            }
        }

        int rows = (groups[g].count + cols - 1) / cols;
        curY += rows * (btnH + padY) + 8;
    }
}
