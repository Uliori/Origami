#include "OResourceManager.h"
#include <Core/Graphics/Renderers/ORendererFactory.h>
#include <string>

namespace Origami {
    OTextureCache OResourceManager::m_TextureCache;

    OTexture OResourceManager::loadTexture(const std::string& texturePath)
    {
        return m_TextureCache.getTexture(texturePath);
    }

    void OResourceManager::checkResources()
    {
        ORendererFactory::initRenderers();
        m_TextureCache.checkTextures();
    }

}