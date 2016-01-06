//
//  ORendererSpriteBatch.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/24/15.
//
//

#include "ORendererSpriteBatch.h"
#include <algorithm>

#include <Core/Graphics/Renderers/ORendererFactory.h>
#include <Core/Graphics/Layers/OLayer2D.h>

//#include "freetype-gl.h"
#include <Core/Graphics/GUI/OFont.h>
#include <Core/Graphics/GUI/OFontManager.h>


NS_O_BEGIN

//Glyph
Glyph::Glyph(const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder) :
textureID(texture) {
    
    a_zOrder = zOrder;
    
    topLeft.m_color = color;
    topLeft.setPosition(position.x, position.y + dimensions.y);
    topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
    
    bottomLeft.m_color = color;
    bottomLeft.setPosition(position.x, position.y);
    bottomLeft.setUV(uvRect.x, uvRect.y);
    
    bottomRight.m_color = color;
    bottomRight.setPosition(position.x + dimensions.x, position.y);
    bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
    
    topRight.m_color = color;
    topRight.setPosition(position.x + dimensions.x, position.y + dimensions.y);
    topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
}


//SpriteBatch
ORendererSpriteBatch::ORendererSpriteBatch(): m_vboID(0), m_vaoID(0)
{
    Init();
}

ORendererSpriteBatch::~ORendererSpriteBatch()
{
    if (m_vboID != 0) {
        glDeleteBuffers(1, &m_vboID);
    }
    
    if (m_vaoID != 0) {
        glDeleteVertexArrays(1, &m_vaoID);
    }
}

void ORendererSpriteBatch::Init()
{
    createVertexArray();
}

void ORendererSpriteBatch::Begin()
{
    m_renderBatches.clear();
    
    // Makes _glpyhs.size() == 0, however it does not free internal memory.
    // So when we later call emplace_back it doesn't need to internally call new.
    m_glyphs.clear();
}

void ORendererSpriteBatch::Submit(const OSprite* renderable)
{
    m_glyphs.emplace_back(renderable->GetPosition(), renderable->GetSize(), renderable->GetUV(), renderable->GetTID(), renderable->GetColor(), renderable->GetZOrder());
}

void ORendererSpriteBatch::DrawString(const std::string& text, const maths::vec3& position, const OFont& font, unsigned int color)
{
    //        using namespace ftgl;
    //
    //        uint ts = font.GetID();
    //
    //
    //        const maths::vec2& scale = font.GetScale();
    //
    //        float x = position.x;
    //        float y = position.y;
    //
    //        texture_font_t* ftFont = font.GetFTFont();
    //
    //        for (uint i = 0; i < text.length(); i++)
    //        {
    //            char c = text[i];
    //            texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);
    //            if (glyph != NULL)
    //            {
    //                if (i > 0)
    //                {
    //                    float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
    //                    x += kerning / scale.x;
    //                }
    //
    //                float x0 = x + glyph->offset_x / scale.x;
    //                float y0 = y + glyph->offset_y / scale.y;
    //                float x1 = x0 + glyph->width / scale.x;
    //                float y1 = y0 - glyph->height / scale.y;
    //
    //                float u0 = glyph->s0;
    //                float v0 = glyph->t0;
    //                float u1 = glyph->s1;
    //                float v1 = glyph->t1;
    //
    //                m_glyphs.emplace_back(maths::vec3(x0, y0, 0), maths::vec2(x1 - x0, y1 - y0), maths::vec4(u0, v0, u1 - u0, v1 - v0), ts, color);
    //
    //                x += glyph->advance_x / scale.x ;
    //
    ////                if (y < position.y - 100) {
    ////                    DrawString("...", maths::vec3(x, y, position.z), font, color);
    ////                    break;
    ////                }
    //                if (x >= position.x + 300) {
    //                    x = position.x;
    //                    y -= ftFont->height;
    //                }
    //
    //
    //            }
    //        }
    //
}

void ORendererSpriteBatch::End()
{
    // Set up all pointers for fast sorting
    m_glyphPointers.resize(m_glyphs.size());
    for (size_t i = 0; i < m_glyphs.size(); i++) {
        m_glyphPointers[i] = &m_glyphs[i];
    }
    
    sortGlyphs();
    createRenderBatches();
}

void ORendererSpriteBatch::Flush(OLayer2D *layer)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ORendererFactory::OShader_Simple2D->bind();
    glActiveTexture(GL_TEXTURE0);
    ORendererFactory::OShader_Simple2D->setUniform1i("u_diffuse", 0);
    ORendererFactory::OShader_Simple2D->setUniformMat4("u_MVP", layer->getCamera()->getCameraMatrix());
    glBindVertexArray(m_vaoID);
    
    for (size_t i = 0; i < m_renderBatches.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
        
        glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
    }
    
    ORendererFactory::OShader_Simple2D->unbind();
    glBindVertexArray(0);
}


void ORendererSpriteBatch::createRenderBatches() {
    // This will store all the vertices that we need to upload
    std::vector <VertexData2D> vertices;
    // Resize the buffer to the exact size we need so we can treat
    // it like an array
    vertices.resize(m_glyphPointers.size() * 6);
    
    if (m_glyphPointers.empty()) {
        return;
    }
    
    int offset = 0; // current offset
    int cv = 0; // current vertex
    
    //Add the first batch
    m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->textureID);
    vertices[cv++] = m_glyphPointers[0]->topLeft;
    vertices[cv++] = m_glyphPointers[0]->bottomLeft;
    vertices[cv++] = m_glyphPointers[0]->bottomRight;
    vertices[cv++] = m_glyphPointers[0]->bottomRight;
    vertices[cv++] = m_glyphPointers[0]->topRight;
    vertices[cv++] = m_glyphPointers[0]->topLeft;
    offset += 6;
    
    //Add all the rest of the glyphs
    for (size_t cg = 1; cg < m_glyphPointers.size(); cg++) {
        
        // Check if this glyph can be part of the current batch
        if (m_glyphPointers[cg]->textureID != m_glyphPointers[cg - 1]->textureID) {
            // Make a new batch
            m_renderBatches.emplace_back(offset, 6, m_glyphPointers[cg]->textureID);
        } else {
            // If its part of the current batch, just increase numVertices
            m_renderBatches.back().numVertices += 6;
        }
        vertices[cv++] = m_glyphPointers[cg]->topLeft;
        vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
        vertices[cv++] = m_glyphPointers[cg]->bottomRight;
        vertices[cv++] = m_glyphPointers[cg]->bottomRight;
        vertices[cv++] = m_glyphPointers[cg]->topRight;
        vertices[cv++] = m_glyphPointers[cg]->topLeft;
        offset += 6;
    }
    
    glBindVertexArray(m_vaoID);
    
    // Bind our VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    // Orphan the buffer (for speed)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData2D), NULL, GL_DYNAMIC_DRAW);
    // Upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(VertexData2D), vertices.data());
    
    glBindVertexArray(0);
    // Unbind the VBO
    //        glBindBuffer(GL_ARRAY_BUFFER, 0);
    
}

void ORendererSpriteBatch::createVertexArray() {
    
    // Generate the VAO if it isn't already generated
    if (m_vaoID == 0) {
        glGenVertexArrays(1, &m_vaoID);
    }
    
    // Bind the VAO. All subsequent opengl calls will modify it's state.
    glBindVertexArray(m_vaoID);
    
    //G enerate the VBO if it isn't already generated
    if (m_vboID == 0) {
        glGenBuffers(1, &m_vboID);
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    
    //Tell opengl what attribute arrays we need
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    glVertexAttribPointer(0, 2, GL_FLOAT,         GL_FALSE, sizeof(VertexData2D), (void *)offsetof(VertexData2D, m_vertex));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE , sizeof(VertexData2D), (void *)offsetof(VertexData2D, m_color));
    glVertexAttribPointer(2, 2, GL_FLOAT        , GL_FALSE, sizeof(VertexData2D), (void *)offsetof(VertexData2D, m_uv));
    
    glBindVertexArray(0);
    
}

void ORendererSpriteBatch::sortGlyphs() {
    
    std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFunction);
    
}

bool ORendererSpriteBatch::compareFunction(Glyph* a, Glyph* b) {
    if (a->a_zOrder == b->a_zOrder) {
        return (a->textureID < b->textureID);
    }
    return (a->a_zOrder < b->a_zOrder);
}

NS_O_END