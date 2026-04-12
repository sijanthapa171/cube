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

struct MoveRecord {
    std::string notation;
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

    const std::vector<MoveRecord>& GetMoveHistory() const { return moveHistory; }
    int GetMoveCount() const { return (int)moveHistory.size(); }
    void ClearHistory() { moveHistory.clear(); redoStack.clear(); }

    void UndoMove();
    void RedoMove();
    bool CanUndo() const { return !moveHistory.empty() && !IsBusy(); }
    bool CanRedo() const { return !redoStack.empty() && !IsBusy(); }

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

    std::vector<MoveRecord> moveHistory;
    std::vector<MoveRecord> redoStack;
};
