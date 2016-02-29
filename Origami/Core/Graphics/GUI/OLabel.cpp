#include "OLabel.hpp"
#include <Core/Graphics/Renderers/ORendererFactory.hpp>

#include <sstream>

NS_O_BEGIN

OLabel::OLabel(const std::string& text)
: m_Text(text), m_Font(OFontManager::get())
{
    init();
}

OLabel::OLabel(const std::string& text, OFont* font)
    : m_Text(text), m_Font(font)
{
    init();
}

void OLabel::init()
{
    m_Position = maths::vec2(0, 0);
    m_Size = maths::vec2(180, 50);
    m_TextColor = OColorRGBA8();
    m_Color = OColorRGBA8(0, 0, 0, 0);
    borders = maths::vec4(2, 2, 2, 2);
    
    getLines();
}

void OLabel::submit(ORenderer2D* renderer) 
{
    maths::vec4 textRect(m_Position.x + borders.x, m_Position.y + borders.y, m_Size.x - borders.x - borders.z, m_Size.y - borders.y - borders.w);
    
    //draw the background color
    renderer->submitBox(ORendererFactory::OShader_Color2D, m_Position, m_Size, maths::vec4(), 0, m_Color.getColorUint(), m_zOrder);
//    //draw the text rect (this is for tests only)
//    renderer->submitBox(ORendererFactory::OShader_Color2D, maths::vec2(textRect.x, textRect.y),
//                        maths::vec2(textRect.z, textRect.w), maths::vec4(),
//                        0, OColorRGBA8(0, 0, 1).getColorUint(),
//                        m_zOrder);
    //draw the text in the rect
    renderer->drawString(ORendererFactory::OShader_Text, m_Lines, m_LinesWidth,
                         Rect(textRect.x, textRect.y, textRect.z, textRect.w), textAlignment, *m_Font,
                         m_TextColor.getColorUint(), m_zOrder+0.0001);
}

float OLabel::getWordWidth(const std::string& word)
{
    float width = 0;
    
    const maths::vec2& scale = m_Font->GetScale();
    ftgl::texture_font_t* ftFont = m_Font->GetFTFont();
    for (uint i = 0; i < word.length(); i++)
    {
        char c = word[i];
        ftgl::texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);
        if (glyph != nullptr) {
            if (i > 0)
            {
                float kerning = texture_glyph_get_kerning(glyph, m_Text[i - 1]);
                width += kerning / scale.x;
            }
            float gwidth = glyph->advance_x / scale.x;
            width += gwidth;
        }
    }
    return width;
}

float OLabel::getCharWidth(const char& c)
{
    float width = 0;
    
    const maths::vec2& scale = m_Font->GetScale();
    ftgl::texture_font_t* ftFont = m_Font->GetFTFont();

    ftgl::texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);
    if (glyph != nullptr) {
        float gwidth = glyph->advance_x / scale.x;
        width += gwidth;
    }
    
    return width;
}

void OLabel::handleAWord(const std::string& word, float& currentLineLength, float width)
{
    float wordWidth = getWordWidth(word);
    if (currentLineLength + wordWidth > width) {
        if (currentLineLength > 0) {
            m_Lines.push_back("");
            m_LinesWidth.push_back(0);
            currentLineLength = 0;
        }
        
        if (wordWidth <= width) {
            handleAWord(word, currentLineLength, width);
        }
        else {
            for(auto& c : word) {
                float cWidth = getCharWidth(c);
                
                if (currentLineLength + cWidth > width && cWidth <= width) {
                    m_Lines.push_back("");
                    m_LinesWidth.push_back(0);
                    currentLineLength = 0;
                }
                else if (cWidth > width){
                    break;
                }
                else
                {
                    m_Lines.back() += c;
                    m_LinesWidth.back() += cWidth;
                    currentLineLength += cWidth;
                }
            }
        }
    }
    else
    {
        currentLineLength += wordWidth;
        m_Lines.back() += word; //add the word to the current line
        m_LinesWidth.back() += wordWidth; //add the word width to the current line width
    }
}

void OLabel::getLines()
{
    m_Lines.clear();
    m_LinesWidth.clear();
    
    std::stringstream stringStream(m_Text);
    std::string line;
    std::vector<std::string> wordVector;
    
    float rectWidth = m_Size.x - borders.x - borders.z;
    
    float currentLineLength = 0;
    while(std::getline(stringStream, line))
    {
        m_Lines.push_back("");
        m_LinesWidth.push_back(0);
        
        std::size_t prev = 0, pos;
        while ((pos = line.find_first_of(" ", prev)) != std::string::npos) //while there is a separator
        {
            if (pos > prev) { // a new word
                //handle the word
                std::string word = line.substr(prev, pos-prev);
                handleAWord(word, currentLineLength, rectWidth);
            }
            prev = pos+1;
            
            //handle the space
            handleAWord(" ", currentLineLength, rectWidth);
        }
        if (prev < line.length()){ //the latest word in a line
            //handle the word
            std::string word = line.substr(prev, std::string::npos);
            handleAWord(word, currentLineLength, rectWidth);
        }
    }
}

void OLabel::sizetoFit()
{
    float fontHeight = m_Font->GetSize() / m_Font->GetScale().y;
    float textHeight = m_Lines.size() * fontHeight;
    m_Size.y = textHeight + borders.y + borders.w;    
}

NS_O_END
