#pragma once

#include "TextureUtils.h"
#include <map>

#include <Core/OMacros.h>

NS_O_BEGIN

class OTextureCache {
public:
    OTextureCache();
    ~OTextureCache();

    OTexture* loadTexture(const std::string& texturePath, bool invert_y = true, GLint param_W_S = GL_CLAMP_TO_EDGE, GLint param_W_T = GL_CLAMP_TO_EDGE);
    OTexture* getTexture(const std::string& texturePath);
    
    void releaseTexture(const std::string& texturePath);

    void checkTextures();
    void reloadTextures();
private:
    std::map<std::string, OTexture *> m_TextureMap;
};

NS_O_END
