#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <string>

struct CubieState {
    Vector3 pos;
    Matrix transform;
    Color up, down, front, back, right, left;
};

struct MoveCmd {
    int axis;
    std::vector<int> slices;
    int direction;
};

class RubiksCube {
public:
    RubiksCube();
    void Update(float dt);
    void Draw();
    
    bool StartRotation(int axis, int slice, int direction);
    bool StartMultiSliceRotation(int axis, const std::vector<int>& slices, int direction);
    void ExecuteMove(const char* notation);
    void RecordMove(int axis, const std::vector<int>& slices, int direction);

    bool IsAnimating() const { return isAnimating; }
    bool IsBusy() const { return isAnimating || !moveQueue.empty(); }

    const std::vector<std::string>& GetMoveHistory() const { return moveHistory; }
    int GetMoveCount() const { return (int)moveHistory.size(); }
    void ClearHistory() { moveHistory.clear(); }

private:
    float cubieSize;
    float spacing;

    std::vector<CubieState> cubies;

    bool isAnimating;
    int animAxis;
    std::vector<int> animSlices;
    int animDir;
    float animAngle;
    float targetAngle;

    std::vector<MoveCmd> moveQueue;
    void ProcessQueue();

    std::vector<std::string> moveHistory;
};
