#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "Animator.h"
#include "TextureManager.h"
#include <string>
#include <unordered_map>
#include <memory>

class AnimatorManager {
private:
    TextureManager& texManager;
    std::unordered_map<std::string, std::unique_ptr<Animator>> animMap;

    void loadAllAnimators();

public:
    AnimatorManager(TextureManager& tm);

    void addAnimator(const std::string& key, std::unique_ptr<Animator> animator);
    Animator* getAnimator(const std::string& key);
};

#endif