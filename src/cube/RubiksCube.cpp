#include "RubiksCube.h"
#include "Cubie.h"

RubiksCube::RubiksCube() : cubieSize(1.0f), spacing(1.05f) {}

void RubiksCube::Draw() {
    Color rWhite  = { 255, 255, 255, 255 };
    Color rYellow = { 255, 213,   0, 255 };
    Color rGreen  = {   0, 158,  96, 255 };
    Color rBlue   = {   0,  81, 186, 255 };
    Color rRed    = { 196,  30,  58, 255 };
    Color rOrange = { 255,  88,   0, 255 };
    Color rBlack  = {  15,  15,  15, 255 };

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            for (int z = -1; z <= 1; z++) {
                Vector3 pos = { (float)x * spacing, (float)y * spacing, (float)z * spacing };

                Color up    = (y ==  1) ? rWhite  : rBlack;
                Color down  = (y == -1) ? rYellow : rBlack;
                Color front = (z ==  1) ? rGreen  : rBlack;
                Color back  = (z == -1) ? rBlue   : rBlack;
                Color right = (x ==  1) ? rRed    : rBlack;
                Color left  = (x == -1) ? rOrange : rBlack;

                DrawCubie(pos, cubieSize, up, down, front, back, right, left);
            }
        }
    }
}
