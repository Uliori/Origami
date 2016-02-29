#pragma once

#include <Core/Graphics/2D/OSprite.hpp>
#include <Core/Maths/OMaths.hpp>
#include "OFontManager.hpp"

#include <Core/OMacros.hpp>

NS_O_BEGIN

enum OTextAlignment
{
    OTEXT_ALIGN_LEFT = 1,
    OTEXT_ALIGN_CENTERED_H = 2,
    OTEXT_ALIGN_RIGHT = 4,
    OTEXT_ALIGN_TOP = 8,
    OTEXT_ALIGN_CENTERED_V = 16,
    OTEXT_ALIGN_CENTERED = 18,
    OTEXT_ALIGN_BOTTOM = 32
};

class OLabel : public OSprite
{
private:
    //Text properties
    OFont* m_Font = nullptr;
    std::string m_Text;
    OColorRGBA8 m_TextColor;
    maths::vec4 borders;
    std::vector<std::string> m_Lines;
    std::vector<float> m_LinesWidth;
    
    int textAlignment = OTEXT_ALIGN_CENTERED;
    
    void getLines();
    void handleAWord(const std::string& word, float& currentLineLength, float width);
    float getWordWidth(const std::string& word);
    float getCharWidth(const char& c);
    
    void init();
public:
    OLabel(const std::string& text, const maths::vec2& position);
    OLabel(const std::string& text, const maths::vec2& position, OFont* font);
    
    void submit(ORenderer2D* renderer)  override;

    inline void setText(const std::string& nt) { m_Text = nt; getLines(); }
    inline void setTextColor(const OColorRGBA8& color) { m_TextColor = color; }
    inline void setFont(OFont* font) { m_Font = font; }
    inline void setTextAlignment(OTextAlignment alignment) { textAlignment = alignment; }
    
    inline void setPadding(int p) { borders = maths::vec4(p, p, p, p); }
    inline void setPadding(int left, int bottom, int right, int top) { borders = maths::vec4(left, bottom, right, top); }
    
    void sizetoFit();
};

NS_O_END
