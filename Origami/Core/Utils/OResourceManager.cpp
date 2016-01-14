#include "OResourceManager.h"
#include <Core/Graphics/Renderers/ORendererFactory.h>
#include <string>

NS_O_BEGIN
OTextureCache * OResourceManager::m_TextureCache;
OTextureCache * OResourceManager::textureCache()
{
    if (m_TextureCache == nullptr) {
        m_TextureCache = new OTextureCache();
    }
    return m_TextureCache;
}

void OResourceManager::checkResources()
{
    ORendererFactory::createRenderers();
    textureCache()->checkTextures();
}

void OResourceManager::reloadResources()
{
    ORendererFactory::createRenderers();
    // textureCache()->reloadTextures();
}

void OResourceManager::cleanUp()
{
    if(m_TextureCache)
        SAFE_DELETE(m_TextureCache);
}

NS_O_END
