#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "AsciiTexture.h"
#include <unordered_map>
#include <string>
#include <memory>

class TextureManager {
private:
    std::unordered_map<std::string, std::shared_ptr<AsciiTexture>> textureMap;
    void loadDefaultTextures();

public:
    TextureManager();

    void addTexture(const std::string& key, std::shared_ptr<AsciiTexture> tex);
    std::shared_ptr<AsciiTexture> getTexture(const std::string& key) const;
};

#endif