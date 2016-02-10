#include "OLabel.hpp"

NS_O_BEGIN

OLabel::OLabel(const std::string& text, float x, float y, OColorRGBA8& color)
    : m_Text(text), m_Font(OFontManager::get("SourceSansPro"))
{
    m_Position = maths::vec2(x, y);
    m_Color = color;
}

OLabel::OLabel(const std::string& text, float x, float y, OFont* font, OColorRGBA8& color)
    : m_Text(text), m_Font(font)
{
    m_Position = maths::vec2(x, y);
    m_Color = color;
}

OLabel::OLabel(const std::string& text, float x, float y, const std::string& font, OColorRGBA8& color)
    : m_Text(text), m_Font(OFontManager::get(font))
{
    m_Position = maths::vec2(x, y);
    m_Color = color;

    validateFont(font);
}

OLabel::OLabel(const std::string& text, float x, float y, const std::string& font, uint size, OColorRGBA8& color)
    : m_Text(text), m_Font(OFontManager::get(font, size))
{
    m_Position = maths::vec2(x, y);
    m_Color = color;

    validateFont(font, size);
}

void OLabel::submit(ORenderer2D* renderer) 
{
//    renderer->DrawString(m_text, m_Position, *m_Font, m_Color);
}

void OLabel::validateFont(const std::string& name, int size)
{
    if (m_Font != nullptr)
        return;

    std::cout << "NULL FONT! Font=" << name;
    if (size > 0)
        std::cout << ", Size=" << size;
    std::cout << std::endl;

    m_Font = OFontManager::get("SourceSansPro");
}

NS_O_END
