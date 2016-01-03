#pragma once

#include "OTextureCache.h"

#include <Core/OMacros.h>

NS_O_BEGIN

class OResourceManager {
public:
    static OTexture loadTexture(const std::string& texturePath);
    
    
    static void checkResources();
    static void cleanUp();
    
private:
    static OTextureCache * textureCache();
    static OTextureCache *m_TextureCache;
};

NS_O_END