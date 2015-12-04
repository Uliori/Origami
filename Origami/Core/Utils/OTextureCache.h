#pragma once

#include "TextureUtils.h"
#include <map>

namespace Origami {

		class OTextureCache {
		public:
			OTextureCache();
			~OTextureCache();

			OTexture getTexture(const std::string& texturePath);
            void checkTextures();
		private:
			std::map<std::string, OTexture> m_TextureMap;
		};

}