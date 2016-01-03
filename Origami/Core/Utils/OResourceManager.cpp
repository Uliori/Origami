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

OTexture OResourceManager::loadTexture(const std::string& texturePath)
{
    return textureCache()->getTexture(texturePath);
}

void OResourceManager::checkResources()
{
    ORendererFactory::initRenderers();
    textureCache()->checkTextures();
}

void OResourceManager::cleanUp()
{
    if(m_TextureCache)
        SAFE_DELETE(m_TextureCache);
}

NS_O_END