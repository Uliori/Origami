#include "OFont.hpp"

#include <Core/Utils/OLog.hpp>
#include <Core/Utils/ResourcesUtils.hpp>
#include <Core/ODirector.hpp>

NS_O_BEGIN

OFont::OFont(const std::string& name, const std::string& filename, float size)
: m_Name(name), m_Filename(filename), m_Scale(maths::vec2(1.0f, 1.0f))
{
#ifdef O_TARGET_MOBILE
    float scale = ODirector::director()->fileExtensions.front().scale;
#else
    float scale = 1;
#endif
    
    m_FTAtlas = ftgl::texture_atlas_new(512 * scale, 512 * scale, 1);
    m_Size = size * scale;
    setScale(scale, scale);
    
    unsigned char* buffer;
    size_t buffer_length;
    ResourcesUtils::fileLength(filename.c_str(), buffer, buffer_length);
    
    m_FTFont = ftgl::texture_font_new_from_memory(m_FTAtlas, size * scale, buffer, buffer_length);
    
    if(!m_FTFont)
        OErrLog("Failed to load font '" <<  filename.c_str() << "'!");
}

OFont::OFont(const std::string& name, const unsigned char* data, unsigned int datasize, float size)
    : m_Name(name), m_Filename("NULL"), m_Size(size), m_Scale(maths::vec2(1.0f, 1.0f))
{
    m_FTAtlas = ftgl::texture_atlas_new(512, 512, 1);
    m_FTFont = ftgl::texture_font_new_from_memory(m_FTAtlas, size, data, datasize);
    if(!m_FTFont)
        OErrLog("Failed to load font from data!");
}

void OFont::setScale(float x, float y)
{
    m_Scale = maths::vec2(x, y);
}

NS_O_END
