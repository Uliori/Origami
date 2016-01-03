#pragma once

#include "TextureUtils.h"
#include <map>

#include <Core/OMacros.h>

NS_O_BEGIN

class OTextureCache {
public:
    OTextureCache();
    ~OTextureCache();

    OTexture getTexture(const std::string& texturePath);
    void checkTextures();
private:
    std::map<std::string, OTexture> m_TextureMap;
};

NS_O_END