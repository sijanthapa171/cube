#include "ui/MoveHistory.h"
#include <string>

void DrawMoveHistory(const RubiksCube& cube) {
    const auto& history = cube.GetMoveHistory();
    int count = (int)history.size();

    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    int panelW = 230;
    int panelH = 220;
    int panelX = sw - panelW - 10;
    int panelY = sh - panelH - 10;

    DrawRectangle(panelX, panelY, panelW, panelH, { 15, 15, 25, 210 });
    DrawRectangleLines(panelX, panelY, panelW, panelH, { 60, 65, 90, 180 });

    DrawText(TextFormat("Move History (%d)", count),
             panelX + 10, panelY + 8, 15, { 130, 200, 255, 255 });

    DrawLine(panelX + 8, panelY + 28, panelX + panelW - 8, panelY + 28,
             { 60, 65, 90, 140 });

    if (count == 0) {
        DrawText("No moves yet", panelX + 10, panelY + 40, 14,
                 { 100, 100, 120, 180 });
        return;
    }

    int bodyX = panelX + 10;
    int bodyY = panelY + 36;
    int bodyW = panelW - 20;
    int bodyBottom = panelY + panelH - 8;

    int chipH = 22;
    int chipPadX = 4;
    int chipPadY = 4;
    int fontSize = 13;

    int maxRows = (bodyBottom - bodyY) / (chipH + chipPadY);
    if (maxRows < 1) maxRows = 1;

    int curX = bodyX;
    int curY = bodyY;
    int rowCount = 0;
    int startIdx = 0;
    if (count > 0) {
        int testX = bodyX;
        int testRows = 1;
        for (int i = 0; i < count; i++) {
            int tw = MeasureText(history[i].c_str(), fontSize) + 12;
            if (tw < 28) tw = 28;
            if (testX + tw > bodyX + bodyW && testX != bodyX) {
                testRows++;
                testX = bodyX;
            }
            testX += tw + chipPadX;
        }

        if (testRows > maxRows) {
            for (startIdx = count - 1; startIdx > 0; startIdx--) {
                testX = bodyX;
                testRows = 1;
                for (int i = startIdx; i < count; i++) {
                    int tw = MeasureText(history[i].c_str(), fontSize) + 12;
                    if (tw < 28) tw = 28;
                    if (testX + tw > bodyX + bodyW && testX != bodyX) {
                        testRows++;
                        testX = bodyX;
                    }
                    testX += tw + chipPadX;
                }
                if (testRows <= maxRows) break;
            }
        }
    }

    if (startIdx > 0) {
        DrawText("...", bodyX, curY + 2, fontSize, { 100, 100, 120, 160 });
        int dotsW = MeasureText("...", fontSize) + 10;
        curX = bodyX + dotsW;
    }

    for (int i = startIdx; i < count; i++) {
        const char* label = history[i].c_str();
        int tw = MeasureText(label, fontSize) + 12;
        if (tw < 28) tw = 28;

        if (curX + tw > bodyX + bodyW && curX != bodyX) {
            curX = bodyX;
            curY += chipH + chipPadY;
            rowCount++;
            if (curY + chipH > bodyBottom) break;
        }

        Color chipBg = ((i % 2) == 0)
            ? (Color){ 40, 45, 65, 200 }
            : (Color){ 50, 55, 80, 200 };

        Color border = { 55, 60, 85, 160 };
        Color textCol = { 220, 225, 245, 255 };
        if (i == count - 1) {
            chipBg = { 60, 80, 140, 230 };
            border = { 120, 150, 255, 200 };
            textCol = { 255, 255, 255, 255 };
        }

        Rectangle chipRect = { (float)curX, (float)curY, (float)tw, (float)chipH };
        DrawRectangleRounded(chipRect, 0.3f, 4, chipBg);
        DrawRectangleRoundedLinesEx(chipRect, 0.3f, 4, 1.0f, border);

        int textX = curX + (tw - MeasureText(label, fontSize)) / 2;
        int textY = curY + (chipH - fontSize) / 2;
        DrawText(label, textX, textY, fontSize, textCol);

        curX += tw + chipPadX;
    }
}
