#pragma once

#include "OTextureCache.h"

namespace Origami {

		class OResourceManager {
		public:
			static OTexture loadTexture(const std::string& texturePath);

		private:
			static OTextureCache m_TextureCache;
		};

}