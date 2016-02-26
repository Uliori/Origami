#pragma once

#include <string>
#include <Core/Maths/OMaths.hpp>

#include "freetype-gl.h"

#include <Core/OMacros.hpp>

NS_O_BEGIN

class OFont
{
private:
    ftgl::texture_atlas_t* m_FTAtlas;
    ftgl::texture_font_t* m_FTFont;
    
    float m_Size;
    maths::vec2 m_Scale;
    std::string m_Name;
    std::string m_Filename;
public:
    OFont(const std::string& name, const std::string& filename, float size);
    OFont(const std::string& name, const unsigned char* data, unsigned int datasize, float size);

    void setScale(float x, float y);

    inline ftgl::texture_font_t* GetFTFont() const { return m_FTFont; }

    inline const unsigned int GetID() const { return m_FTAtlas->id; }
    inline const maths::vec2& GetScale() const { return m_Scale; }
    inline const std::string& GetName() const { return m_Name; }
    inline const std::string& GetFileName() const { return m_Filename; }
    inline const float GetSize() const { return m_Size; }
};

NS_O_END
