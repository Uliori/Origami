#pragma once

#include <Core/Graphics/2D/OSprite.h>
#include "OFontManager.h"

#include <Core/OMacros.h>

NS_O_BEGIN

class OLabel : public OSprite
{
private:
    OFont* m_Font;
    std::string m_Text;
    float m_X, m_Y;
public:
    OLabel(const std::string& text, float x, float y, uint color);
    OLabel(const std::string& text, float x, float y, OFont* font, uint color);
    OLabel(const std::string& text, float x, float y, const std::string& font, uint color);
    OLabel(const std::string& text, float x, float y, const std::string& font, uint size, uint color);
    void submit(ORenderer2D* renderer) const override;
    void validateFont(const std::string& name, int size = -1);

    inline void setText(const std::string& nt) {m_Text = nt;}
};

NS_O_END
