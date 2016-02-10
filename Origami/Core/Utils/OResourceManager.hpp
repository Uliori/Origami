#pragma once

#include "OTextureCache.hpp"

#include <Core/OMacros.hpp>

NS_O_BEGIN

class OResourceManager {
public:
    static OTextureCache * textureCache();

    static void checkResources();
    static void reloadResources();
    static void cleanUp();

private:
    
    static OTextureCache *m_TextureCache;
};

NS_O_END
