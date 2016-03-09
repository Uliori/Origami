//
//  ORendererSpriteBatch.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/24/15.
//
//

#include "ORendererSpriteBatch.hpp"
#include <algorithm>

#include <Core/Graphics/Renderers/ORendererFactory.hpp>
#include <Core/Graphics/Layers/OLayer2D.hpp>

//#include "freetype-gl.h"
#include <Core/Graphics/GUI/OFont.hpp>
#include <Core/Graphics/GUI/OFontManager.hpp>


NS_O_BEGIN

//SpriteBatch
ORendererSpriteBatch::ORendererSpriteBatch(): m_VboID(0), m_VaoID(0)
{
    
}

ORendererSpriteBatch::~ORendererSpriteBatch()
{
    if (m_VboID != 0) {
        glDeleteBuffers(1, &m_VboID);
    }

    if (m_VaoID != 0) {
        glDeleteVertexArrays(1, &m_VaoID);
    }
}

void ORendererSpriteBatch::init()
{
    createVertexArray();
}

void ORendererSpriteBatch::begin()
{
    m_RenderBatches.clear();

    // Makes _glpyhs.size() == 0, however it does not free internal memory.
    // So when we later call emplace_back it doesn't need to internally call new.
    m_Glyphs.clear();
}

void ORendererSpriteBatch::submitBox(OShader *shader, const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder)
{
    m_Glyphs.emplace_back(shader, position, dimensions, uvRect, texture, color, zOrder);
}

void ORendererSpriteBatch::submitBox(OShader *shader, const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder, float angle)
{
    m_Glyphs.emplace_back(shader, position, dimensions, uvRect, texture, color, zOrder, angle);
}

void ORendererSpriteBatch::submitBox(OShader *shader, const VertexData2D &atopLeft,const VertexData2D &abottomLeft,const VertexData2D &atopRight,const VertexData2D &abottomRight, GLuint texture, float zOrder)
{
    m_Glyphs.emplace_back(shader, atopLeft, abottomLeft, atopRight, abottomRight, texture, zOrder);
}

void ORendererSpriteBatch::submitBox(OShader *shader, const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder, const maths::vec2& dir)
{
    const maths::vec2 right(1.0f, 0.0f);
    float angle = acos(maths::dot(right, dir));
    if (dir.y < 0.0f) angle = -angle;
    
    m_Glyphs.emplace_back(shader, position, dimensions, uvRect, texture, color, zOrder, angle);
}

void ORendererSpriteBatch::submitPolygon(const std::vector<Glyph>& glyphs)
{
    m_Glyphs.insert(m_Glyphs.end(), glyphs.begin(), glyphs.end());
}

void ORendererSpriteBatch::drawString(OShader *shader, const std::vector<std::string>& Lines, const std::vector<float>& LinesLength, const Rect& rect, int alignment, const OFont& font, unsigned int color, float zOrder)
{
    //Get font data
    using namespace ftgl;
    uint ts = font.GetID();
    if (ts == 0) {
        return;
    }
    texture_font_t* ftFont = font.GetFTFont();
    const maths::vec2& scale = font.GetScale();
    float fontHeight = font.GetSize() / scale.y;
    //
    
    float startX = rect.origin.x;
    float startY = rect.origin.y + rect.size.height - (fontHeight + (ftFont->descender / scale.y)); // need to substract only the origin point

    float x = startX;
    float y = startY;

    //get the number of lines that can be rendered inside the rect, given a font size;
    int nbrOfLines = 0;
    float textHeightTMP = 0;
    for (int i = 0; i < Lines.size(); i++) {
        if (textHeightTMP + fontHeight <= rect.size.height) {
            textHeightTMP += fontHeight;
            nbrOfLines++;
        }
        else
        {
            break;
        }
    }
    //if the font size is greater than the rect height, or if there is no line to render
    if (nbrOfLines  == 0) {
        return;
    }
    //
    
    //the height of the actual text to render
    float textHeight = nbrOfLines * fontHeight;
    
    
    //Text vertical alignment
    if (alignment & OTextAlignment::OTEXT_ALIGN_TOP)
        y = startY;
    else if (alignment & OTextAlignment::OTEXT_ALIGN_CENTERED_V)
        y = startY - (rect.size.height - textHeight)/2 ;
    else if (alignment & OTextAlignment::OTEXT_ALIGN_BOTTOM)
        y = startY - (rect.size.height - textHeight);

    
    for (int i = 0; i < nbrOfLines; i++) {
        const std::string& text = Lines[i];
        float lineWidth = LinesLength[i];
        
        //Text horizontal alignment
        if (alignment & OTextAlignment::OTEXT_ALIGN_LEFT)
            x = startX;
        else if (alignment & OTextAlignment::OTEXT_ALIGN_CENTERED_H)
            x = startX + (rect.size.width - lineWidth)/2;
        else if (alignment & OTextAlignment::OTEXT_ALIGN_RIGHT)
            x = startX + (rect.size.width - lineWidth);
        
        for (uint i = 0; i < text.length(); i++)
        {
            char c = text[i];
            texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);
            if (glyph != NULL)
            {
                if (i > 0)
                {
                    float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
                    x += kerning / scale.x;
                }
                
                float x0 = x + glyph->offset_x / scale.x;
                float y0 = y + glyph->offset_y / scale.y;
                float x1 = x0 + glyph->width / scale.x;
                float y1 = y0 - glyph->height / scale.y;
                
                
                
                float u0 = glyph->s0;
                float v0 = glyph->t0;
                float u1 = glyph->s1;
                float v1 = glyph->t1;
                
                if (c == ' ')
                {
                    x += glyph->advance_x / scale.x ;
                    continue;
                }
                
                m_Glyphs.emplace_back(shader, maths::vec2(x0, y0), maths::vec2(x1 - x0, y1 - y0), maths::vec4(u0, v0, u1 - u0, v1 - v0), ts, color, zOrder);
                
                x += glyph->advance_x / scale.x ;
                
            }
        }
        
        x = startX;
        y -= fontHeight;
        
    }
}

void ORendererSpriteBatch::end()
{
    // Set up all pointers for fast sorting
    m_GlyphPointers.resize(m_Glyphs.size());
    for (size_t i = 0; i < m_Glyphs.size(); i++) {
        m_GlyphPointers[i] = &m_Glyphs[i];
    }

    sortGlyphs();
    createRenderBatches();
}

void ORendererSpriteBatch::flush(OCamera2D *camera)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(m_VaoID);

    for (size_t i = 0; i < m_RenderBatches.size(); i++) {
        
        m_RenderBatches[i].currentShader->bind();
        m_RenderBatches[i].currentShader->prepare(camera);
        glBindTexture(GL_TEXTURE_2D, m_RenderBatches[i].texture);
        glDrawArrays(GL_TRIANGLES, m_RenderBatches[i].offset, m_RenderBatches[i].numVertices);
    }

    ORendererFactory::OShader_Texture2D->unbind();
    glBindVertexArray(0);
}


void ORendererSpriteBatch::createRenderBatches() {
    // This will store all the vertices that we need to upload
    std::vector <VertexData2D> vertices;
    // Resize the buffer to the exact size we need so we can treat
    // it like an array
    vertices.resize(m_GlyphPointers.size() * 6);

    if (m_GlyphPointers.empty()) {
        return;
    }

    int offset = 0; // current offset
    int cv = 0; // current vertex

    //Add the first batch
    m_RenderBatches.emplace_back(offset, 6, m_GlyphPointers[0]->textureID, m_GlyphPointers[0]->currentShader);
    vertices[cv++] = m_GlyphPointers[0]->topLeft;
    vertices[cv++] = m_GlyphPointers[0]->bottomLeft;
    vertices[cv++] = m_GlyphPointers[0]->bottomRight;
    vertices[cv++] = m_GlyphPointers[0]->bottomRight;
    vertices[cv++] = m_GlyphPointers[0]->topRight;
    vertices[cv++] = m_GlyphPointers[0]->topLeft;
    offset += 6;

    //Add all the rest of the glyphs
    for (size_t cg = 1; cg < m_GlyphPointers.size(); cg++) {

        // Check if this glyph can be part of the current batch
        if (m_GlyphPointers[cg]->textureID != m_GlyphPointers[cg - 1]->textureID || m_GlyphPointers[cg]->currentShader != m_GlyphPointers[cg - 1]->currentShader) {
            // Make a new batch
            m_RenderBatches.emplace_back(offset, 6, m_GlyphPointers[cg]->textureID, m_GlyphPointers[cg]->currentShader);
        } else {
            // If its part of the current batch, just increase numVertices
            m_RenderBatches.back().numVertices += 6;
        }
        vertices[cv++] = m_GlyphPointers[cg]->topLeft;
        vertices[cv++] = m_GlyphPointers[cg]->bottomLeft;
        vertices[cv++] = m_GlyphPointers[cg]->bottomRight;
        vertices[cv++] = m_GlyphPointers[cg]->bottomRight;
        vertices[cv++] = m_GlyphPointers[cg]->topRight;
        vertices[cv++] = m_GlyphPointers[cg]->topLeft;
        offset += 6;
    }

    glBindVertexArray(m_VaoID);

    // Bind our VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
    // Orphan the buffer (for speed)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData2D), NULL, GL_DYNAMIC_DRAW);
    // Upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(VertexData2D), vertices.data());

    glBindVertexArray(0);

}

void ORendererSpriteBatch::createVertexArray() {

    // Generate the VAO if it isn't already generated
    if (m_VaoID == 0) {
        glGenVertexArrays(1, &m_VaoID);
    }

    // Bind the VAO. All subsequent opengl calls will modify it's state.
    glBindVertexArray(m_VaoID);

    //G enerate the VBO if it isn't already generated
    if (m_VboID == 0) {
        glGenBuffers(1, &m_VboID);
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_VboID);

    //Tell opengl what attribute arrays we need
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 2, GL_FLOAT,         GL_FALSE, sizeof(VertexData2D), (void *)offsetof(VertexData2D, m_Vertex));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE , sizeof(VertexData2D), (void *)offsetof(VertexData2D, m_Color));
    glVertexAttribPointer(2, 2, GL_FLOAT        , GL_FALSE, sizeof(VertexData2D), (void *)offsetof(VertexData2D, m_UV));

    glBindVertexArray(0);

}

void ORendererSpriteBatch::sortGlyphs() {
    std::stable_sort(m_GlyphPointers.begin(), m_GlyphPointers.end(), compareFunction);
}

bool ORendererSpriteBatch::compareFunction(Glyph* a, Glyph* b) {
    if (a->a_zOrder == b->a_zOrder) {
        return (a->textureID < b->textureID);
    }
    return (a->a_zOrder < b->a_zOrder);
}

NS_O_END
