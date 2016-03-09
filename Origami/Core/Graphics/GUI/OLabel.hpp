#pragma once

#include "OWidget.hpp"
#include <Core/Maths/OMaths.hpp>
#include "OFontManager.hpp"

#include <Core/OMacros.hpp>
#include <string>

NS_O_BEGIN

enum OTextAlignment
{
    OTEXT_ALIGN_LEFT = 1,
    OTEXT_ALIGN_CENTERED_H = 2,
    OTEXT_ALIGN_RIGHT = 4,
    
    OTEXT_ALIGN_TOP = 8,
    OTEXT_ALIGN_CENTERED_V = 16,
    OTEXT_ALIGN_BOTTOM = 32,
    
    OTEXT_ALIGN_TOP_LEFT        = OTEXT_ALIGN_LEFT          | OTEXT_ALIGN_TOP,
    OTEXT_ALIGN_CENTERV_LEFT    = OTEXT_ALIGN_LEFT          | OTEXT_ALIGN_CENTERED_V,
    OTEXT_ALIGN_BOTTOM_LEFT     = OTEXT_ALIGN_LEFT          | OTEXT_ALIGN_BOTTOM,
    OTEXT_ALIGN_TOP_CENTERH     = OTEXT_ALIGN_CENTERED_H    | OTEXT_ALIGN_TOP,
    OTEXT_ALIGN_CENTERED        = OTEXT_ALIGN_CENTERED_H    | OTEXT_ALIGN_CENTERED_V,
    OTEXT_ALIGN_BOTTOM_CENTERH  = OTEXT_ALIGN_CENTERED_H    | OTEXT_ALIGN_BOTTOM,
    OTEXT_ALIGN_TOP_RIGHT       = OTEXT_ALIGN_RIGHT         | OTEXT_ALIGN_TOP,
    OTEXT_ALIGN_CENTERV_RIGHT   = OTEXT_ALIGN_RIGHT         | OTEXT_ALIGN_CENTERED_V,
    OTEXT_ALIGN_BOTTOM_RIGHT    = OTEXT_ALIGN_RIGHT         | OTEXT_ALIGN_BOTTOM,
};

class OLabel : public OWidget
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
    OLabel(const std::string& text);
    OLabel(const std::string& text, OFont* font);
    virtual ~OLabel();
    
    void submit(ORenderer2D* renderer)  override;

    inline void setText(const std::string& nt) { m_Text = nt; getLines(); }
    inline void setTextColor(const OColorRGBA8& color) { m_TextColor = color; }
    inline void setBackgroundColor(const OColorRGBA8& color) { m_Color = color; }
    inline void setFont(OFont* font) { m_Font = font; }
    inline void setTextAlignment(int alignment) { textAlignment = alignment; }
    
    void setBackgroundImage(const std::string& texturePath);
    
    inline void setPadding(int p) { borders = maths::vec4(p, p, p, p); }
    inline void setPadding(int left, int bottom, int right, int top) { borders = maths::vec4(left, bottom, right, top); }
    
    void sizetoFit();
    
    virtual void touchEvent(int touchID, TouchPoint::TouchEvent state, const maths::vec2& position, const maths::vec2& lastPosition) override;
};

NS_O_END
