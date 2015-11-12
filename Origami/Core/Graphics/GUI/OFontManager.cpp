#include "OFontManager.h"
#include <Core/Utils/OGLUtils.h>

namespace Origami {

	std::vector<OFont*> OFontManager::m_Fonts;

	void OFontManager::Add(OFont* font)
	{
		m_Fonts.push_back(font);
	}

	OFont* OFontManager::Get()
	{
		return m_Fonts[0];
	}

	OFont* OFontManager::Get(const std::string& name)
	{
		for (OFont* font : m_Fonts)
		{
			if (font->GetName() == name)
				return font;
		}
		// TODO: Maybe return a default font instead?
		return nullptr;
	}

	OFont* OFontManager::Get(const std::string& name, unsigned int size)
	{
		for (OFont* font : m_Fonts)
		{
			if (font->GetSize() == size && font->GetName() == name)
				return font;
		}
		// TODO: Maybe return a default font instead?
		return nullptr;
	}

	void OFontManager::Clean()
	{
		for (uint i = 0; i < m_Fonts.size(); i++)
			delete m_Fonts[i];
	}

}