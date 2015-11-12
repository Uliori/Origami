#include "OTextureCache.h"

#include <string>

namespace Origami {

		OTextureCache::OTextureCache() {

		}

		OTextureCache::~OTextureCache() {
            for (auto iterator : m_TextureMap) {
                OTexture texture = iterator.second;
                glDeleteTextures(1, &texture.textureID);
            }
            
            OLog("Textures deleted !");
		}
        
		OTexture OTextureCache::getTexture(const std::string& texturePath) {
			//lookup the texture and see if its in the map
			auto mit = m_TextureMap.find(texturePath);

			//check if its not in the map
			if (mit == m_TextureMap.end()) {
				//Load the texture
				OTexture newTexture = TextureUtils::loadTexture(texturePath.c_str());

				//Insert it into the map
				m_TextureMap.insert(make_pair(texturePath, newTexture));

				return newTexture;
			}
			return mit->second;
		}

}