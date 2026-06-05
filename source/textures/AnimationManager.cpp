#include "headers/textures/AnimatorManager.h"

AnimatorManager::AnimatorManager(TextureManager& tm) : texManager(tm) {
    loadAllAnimators();
}

void AnimatorManager::loadAllAnimators() {

    
    auto temp = std::make_unique<Animator>();

    // --- Player Animation ---
    temp->addFrame(DirType::DOWN, texManager.getTexture("player-front-0"));
    temp->addFrame(DirType::DOWN, texManager.getTexture("player-front-1"));
    temp->addFrame(DirType::UP, texManager.getTexture("player-back-0"));
    temp->addFrame(DirType::UP, texManager.getTexture("player-back-1"));
    temp->addFrame(DirType::LEFT, texManager.getTexture("player-left-0"));
    temp->addFrame(DirType::LEFT, texManager.getTexture("player-left-1"));
    temp->addFrame(DirType::RIGHT, texManager.getTexture("player-right-0"));
    temp->addFrame(DirType::RIGHT, texManager.getTexture("player-right-1"));
    temp->setTicksPerFrame(7);

    addAnimator("player", std::move(temp));

    // --- Relic Animation ---
    temp = std::make_unique<Animator>();

    temp->addFrame(DirType::DEFAULT, this->texManager.getTexture("relic_0"));
    temp->addFrame(DirType::DEFAULT, this->texManager.getTexture("relic_1"));
    temp->addFrame(DirType::DEFAULT, this->texManager.getTexture("relic_2"));
    temp->addFrame(DirType::DEFAULT, this->texManager.getTexture("relic_3"));
    temp->setTicksPerFrame(20);

    addAnimator("relic", std::move(temp));
}

void AnimatorManager::addAnimator(const std::string& key, std::unique_ptr<Animator> animator) {
    if (animator) {
        animMap[key] = std::move(animator);
    }
}

Animator* AnimatorManager::getAnimator(const std::string& key) {
    if (animMap.count(key)) {
        return animMap.at(key).get();
    }
    return nullptr;
}