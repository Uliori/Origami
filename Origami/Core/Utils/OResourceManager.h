#pragma once

#include "OTextureCache.h"

namespace Origami {

		class OResourceManager {
		public:
			static OTexture loadTexture(const std::string& texturePath);
            
            
            static void checkResources();
		private:
			static OTextureCache m_TextureCache;
		};

}