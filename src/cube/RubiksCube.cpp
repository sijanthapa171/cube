#include "cube/RubiksCube.h"
#include "cube/Cubie.h"
#include <math.h>
#include <cstring>

RubiksCube::RubiksCube() : 
    cubieSize(1.0f), spacing(1.05f), 
    isAnimating(false), animAxis(0), animDir(1), animAngle(0.0f), targetAngle(0.0f) 
{
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
                CubieState c;
                c.pos = { (float)x * spacing, (float)y * spacing, (float)z * spacing };
                c.transform = MatrixTranslate(c.pos.x, c.pos.y, c.pos.z);
                
                c.up    = (y ==  1) ? rWhite  : rBlack;
                c.down  = (y == -1) ? rYellow : rBlack;
                c.front = (z ==  1) ? rGreen  : rBlack;
                c.back  = (z == -1) ? rBlue   : rBlack;
                c.right = (x ==  1) ? rRed    : rBlack;
                c.left  = (x == -1) ? rOrange : rBlack;

                cubies.push_back(c);
            }
        }
    }
}

bool RubiksCube::StartRotation(int axis, int slice, int direction) {
    return StartMultiSliceRotation(axis, {slice}, direction);
}

bool RubiksCube::StartMultiSliceRotation(int axis, const std::vector<int>& slices, int direction) {
    if (isAnimating) return false;
    
    isAnimating = true;
    animAxis = axis;
    animSlices = slices;
    animDir = direction;
    animAngle = 0.0f;
    targetAngle = (PI / 2.0f) * direction;
    
    return true;
}

void RubiksCube::RecordMove(int axis, const std::vector<int>& slices, int direction) {
    struct MoveMap { int axis; std::vector<int> sl; int baseDir; const char* name; };
    MoveMap maps[] = {
        {0, {1},        1,  "R"}, {0, {-1},       -1, "L"},
        {1, {1},        1,  "U"}, {1, {-1},       -1, "D"},
        {2, {1},        1,  "F"}, {2, {-1},       -1, "B"},
        {0, {0},       -1,  "M"}, {1, {0},        -1, "E"}, {2, {0}, 1, "S"},
        {0, {-1,0,1},   1,  "x"}, {1, {-1,0,1},   1, "y"}, {2, {-1,0,1}, 1, "z"},
        {0, {0,1},       1,  "r"}, {0, {-1,0},    -1, "l"},
        {1, {0,1},       1,  "u"}, {1, {-1,0},    -1, "d"},
        {2, {0,1},       1,  "f"}, {2, {-1,0},    -1, "b"},
    };

    for (auto& m : maps) {
        if (m.axis == axis && m.sl == slices) {
            std::string notation = m.name;
            if (direction != m.baseDir) notation += "'";
            moveHistory.push_back({ notation, axis, slices, direction });
            redoStack.clear();
            return;
        }
    }
    std::string label = "A" + std::to_string(axis) + "S";
    for (int s : slices) label += std::to_string(s);
    if (direction < 0) label += "'";
    moveHistory.push_back({ label, axis, slices, direction });
    redoStack.clear();
}

void RubiksCube::ProcessQueue() {
    if (moveQueue.empty()) return;
    
    MoveCmd cmd = moveQueue.front();
    moveQueue.erase(moveQueue.begin());
    StartMultiSliceRotation(cmd.axis, cmd.slices, cmd.direction);
}

void RubiksCube::ExecuteMove(const char* notation) {
    if (IsBusy()) return;

    int len = strlen(notation);
    if (len == 0) return;

    char face = notation[0];
    bool prime = (len >= 2 && notation[1] == '\'');
    bool dbl   = (len >= 2 && notation[1] == '2');

    int axis = 0, dir = 1;
    std::vector<int> slices;

    if (face == 'R') {
        axis = 0; slices = {1}; dir = 1;
    } else if (face == 'L') {
        axis = 0; slices = {-1}; dir = -1;
    } else if (face == 'U') {
        axis = 1; slices = {1}; dir = 1;
    } else if (face == 'D') {
        axis = 1; slices = {-1}; dir = -1;
    } else if (face == 'F') {
        axis = 2; slices = {1}; dir = 1;
    } else if (face == 'B') {
        axis = 2; slices = {-1}; dir = -1;
    }
    else if (face == 'M') {
        axis = 0; slices = {0}; dir = -1;
    } else if (face == 'E') {
        axis = 1; slices = {0}; dir = -1;
    } else if (face == 'S') {
        axis = 2; slices = {0}; dir = 1;
    }
    else if (face == 'x') {
        axis = 0; slices = {-1, 0, 1}; dir = 1;
    } else if (face == 'y') {
        axis = 1; slices = {-1, 0, 1}; dir = 1;
    } else if (face == 'z') {
        axis = 2; slices = {-1, 0, 1}; dir = 1;
    }
    else if (face == 'r') {
        axis = 0; slices = {0, 1}; dir = 1;
    } else if (face == 'l') {
        axis = 0; slices = {-1, 0}; dir = -1;
    } else if (face == 'u') {
        axis = 1; slices = {0, 1}; dir = 1;
    } else if (face == 'd') {
        axis = 1; slices = {-1, 0}; dir = -1;
    } else if (face == 'f') {
        axis = 2; slices = {0, 1}; dir = 1;
    } else if (face == 'b') {
        axis = 2; slices = {-1, 0}; dir = -1;
    }
    else {
        return;
    }

    if (prime) dir = -dir;

    if (dbl) {
        moveHistory.push_back({ std::string(notation), axis, slices, dir });
        redoStack.clear();
        MoveCmd cmd = { axis, slices, dir };
        StartMultiSliceRotation(cmd.axis, cmd.slices, cmd.direction);
        moveQueue.push_back(cmd);
    } else {
        moveHistory.push_back({ std::string(notation), axis, slices, dir });
        redoStack.clear();
        StartMultiSliceRotation(axis, slices, dir);
    }
}

void RubiksCube::UndoMove() {
    if (moveHistory.empty() || IsBusy()) return;
    MoveRecord last = moveHistory.back();
    moveHistory.pop_back();
    redoStack.push_back(last);
    StartMultiSliceRotation(last.axis, last.slices, -last.direction);
}

void RubiksCube::RedoMove() {
    if (redoStack.empty() || IsBusy()) return;
    MoveRecord rec = redoStack.back();
    redoStack.pop_back();
    moveHistory.push_back(rec);
    StartMultiSliceRotation(rec.axis, rec.slices, rec.direction);
}

void RubiksCube::Update(float dt) {
    if (!isAnimating) {
        ProcessQueue();
        if (!isAnimating) return;
    }

    float speed = PI * 2.0f * dt; 
    
    bool finished = false;
    float step = speed * ((targetAngle > 0) ? 1.0f : -1.0f);
    
    if (fabs(animAngle + step) >= fabs(targetAngle)) {
        step = targetAngle - animAngle;
        finished = true;
    }
    animAngle += step;

    Matrix rotMat = MatrixIdentity();
    if (animAxis == 0) rotMat = MatrixRotateX(step);
    else if (animAxis == 1) rotMat = MatrixRotateY(step);
    else if (animAxis == 2) rotMat = MatrixRotateZ(step);

    for (auto& c : cubies) {
        int lx = round(c.pos.x / spacing);
        int ly = round(c.pos.y / spacing);
        int lz = round(c.pos.z / spacing);

        bool inSlice = false;
        for (int s : animSlices) {
            if (animAxis == 0 && lx == s) inSlice = true;
            if (animAxis == 1 && ly == s) inSlice = true;
            if (animAxis == 2 && lz == s) inSlice = true;
        }

        if (inSlice) {
            c.pos = Vector3Transform(c.pos, rotMat);
            c.transform = MatrixMultiply(c.transform, rotMat);
            
            if (finished) {
                c.pos.x = round(c.pos.x / spacing) * spacing;
                c.pos.y = round(c.pos.y / spacing) * spacing;
                c.pos.z = round(c.pos.z / spacing) * spacing;
            }
        }
    }

    if (finished) {
        isAnimating = false;
    }
}

void RubiksCube::Draw() {
    for (const auto& c : cubies) {
        DrawCubie(c.transform, cubieSize, c.up, c.down, c.front, c.back, c.right, c.left);
    }
}
