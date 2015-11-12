#pragma once

#include <vector>

#include "OFont.h"

namespace Origami {

	class OFontManager
	{
	private:
		static std::vector<OFont*> m_Fonts;
	public:
		static void Add(OFont* font);
		static OFont* Get();
		static OFont* Get(const std::string& name);
		static OFont* Get(const std::string& name, unsigned int size);
		static void Clean();
	private:
		OFontManager() { }
	};

}