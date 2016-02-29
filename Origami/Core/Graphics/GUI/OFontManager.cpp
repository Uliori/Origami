#include "OFontManager.hpp"
#include <Core/Utils/OGLUtils.hpp>
#include <Core/OTypes.hpp>

NS_O_BEGIN

std::vector<OFont*> OFontManager::m_Fonts;

void OFontManager::add(OFont* font)
{
    m_Fonts.push_back(font);
}

OFont* OFontManager::get()
{
    if (m_Fonts.size() > 0) {
        return m_Fonts[0];
    }
    return nullptr;
}

OFont* OFontManager::get(const std::string& name)
{
    for (OFont* font : m_Fonts)
    {
        if (font->GetName() == name)
            return font;
    }
    //return the default font
    return get();
}

OFont* OFontManager::get(const std::string& name, unsigned int size)
{
    for (OFont* font : m_Fonts)
    {
        if (font->GetSize() == size && font->GetName() == name)
            return font;
    }
    //return the default font
    return get();
}

void OFontManager::clean()
{
    for (uint i = 0; i < m_Fonts.size(); i++)
        delete m_Fonts[i];
    
    m_Fonts.clear();
}

NS_O_END
