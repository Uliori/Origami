#include "OResourceManager.h"

#include <string>

namespace Origami {
		OTextureCache OResourceManager::m_TextureCache;

		OTexture OResourceManager::loadTexture(const std::string& texturePath)
		{
			return m_TextureCache.getTexture(texturePath);
		}

}