#include "headers/textures/Animator.h"

Animator::Animator()
    : currentFrameIdx(0), lastDirType(DirType::DOWN), tickCounter(0), ticksPerFrame(5), isFirstFrame(true) {
    //hello there again
}

DirType Animator::vectorToDir(const Vec2d& dir) const {
    if (std::abs(dir.x) > std::abs(dir.y)) {
        return (dir.x > 0) ? DirType::RIGHT : DirType::LEFT;
    }
    else {
        return (dir.y > 0) ? DirType::DOWN : DirType::UP;
    }
}

void Animator::addFrame(DirType type, std::shared_ptr<AsciiTexture> tex) {
    if (tex) {
        animations[type].push_back(tex);
    }
}

void Animator::drawDirection(const Vec2d& pos, const Vec2d& dir) {
    DirType currentDirType = vectorToDir(dir);

    if (currentDirType != lastDirType) {
        currentFrameIdx = 0;
        lastDirType = currentDirType;
    }

    if (animations[currentDirType].empty()) return;

    auto& currentFrames = animations[currentDirType];
    currentFrames[currentFrameIdx]->printTexture(static_cast<int>(pos.y), static_cast<int>(pos.x));
    
    if (pos.x == lastPos.x && pos.y == lastPos.y) {
        lastPos = pos;
        return;
    }

    tickCounter++;

    if (tickCounter >= ticksPerFrame) {
        tickCounter = 0;
        currentFrameIdx++;

        if (currentFrameIdx >= static_cast<int>(currentFrames.size())) {
            currentFrameIdx = 0;
        }
    }

    lastPos = pos;
}

void Animator::draw(const Vec2d& pos) {
    if (lastDirType != DirType::DEFAULT) {
        currentFrameIdx = 0;
        tickCounter = 0;
        lastDirType = DirType::DEFAULT;
    }

    if (animations[DirType::DEFAULT].empty()) return;

    auto& currentFrames = animations[DirType::DEFAULT];

    if (isFirstFrame) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, static_cast<int>(currentFrames.size()) - 1);

        currentFrameIdx = distr(gen);
        tickCounter = 0;
        isFirstFrame = false;
    }

    currentFrames[currentFrameIdx]->printTexture(static_cast<int>(pos.y), static_cast<int>(pos.x));

    tickCounter++;
    if (tickCounter >= ticksPerFrame) {
        tickCounter = 0;
        currentFrameIdx++;

        if (currentFrameIdx >= static_cast<int>(currentFrames.size())) {
            currentFrameIdx = 0;
        }
    }
}

void Animator::setTicksPerFrame(int ticks) {
    if (ticks > 0) {
        ticksPerFrame = ticks;
    }
}
