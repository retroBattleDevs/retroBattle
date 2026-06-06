#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "AsciiTexture.h"
#include "headers/Vec2d.h"
#include <vector>
#include <map>
#include <memory>
#include <random>

// Internal helper enum to keep the map logic clean
enum class DirType { UP, DOWN, LEFT, RIGHT, DEFAULT };

class Animator {
private:
    std::map<DirType, std::vector<std::shared_ptr<AsciiTexture>>> animations;

    int currentFrameIdx;
    DirType lastDirType;
    Vec2d lastPos;

    int tickCounter;
    int ticksPerFrame;
    bool isFirstFrame;

    DirType vectorToDir(const Vec2d& dir) const;

public:
    Animator();

    void addFrame(DirType type, std::shared_ptr<AsciiTexture> tex);
    
    void drawDirection(const Vec2d& pos, const Vec2d& dir);
    void draw(const Vec2d& pos);

    void setTicksPerFrame(int ticks);
};

#endif