#pragma once

#include "OTextureCache.h"

#include <Core/OMacros.h>

NS_O_BEGIN

class OResourceManager {
public:
    static OTexture loadTexture(const std::string& texturePath, bool invert_y = true, GLint param_W_S = GL_CLAMP_TO_EDGE, GLint param_W_T = GL_CLAMP_TO_EDGE);
    
    
    static void checkResources();
    static void cleanUp();
    
private:
    static OTextureCache * textureCache();
    static OTextureCache *m_TextureCache;
};

NS_O_END