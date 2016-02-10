//
//  ORendererSpriteBatch.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/24/15.
//
//

#pragma once


#include <Core/Graphics/Renderers/ORenderer2D.h>
#include <Core/Graphics/2D/Vertex2D.h>
#include <Core/Graphics/2D/OSprite.h>

#include <vector>

#include <Core/OMacros.h>

NS_O_BEGIN

class Glyph {
public:
    Glyph() {};
    Glyph(const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder);
    Glyph(const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder, float angle);

    GLuint textureID;

    VertexData2D topLeft;
    VertexData2D bottomLeft;
    VertexData2D topRight;
    VertexData2D bottomRight;

    float a_zOrder;
    
private:
    maths::vec2 rotatePoint(const maths::vec2& pos, float angle);
};

// Each render batch is used for a single draw call
class RenderBatch {
public:
    RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture)
    :offset(Offset),numVertices(NumVertices), texture(Texture) {}
    GLuint offset;
    GLuint numVertices;
    GLuint texture;
};


class ORendererSpriteBatch : public ORenderer2D
{
public:
    ORendererSpriteBatch();
    virtual ~ORendererSpriteBatch();

    void init() override;
    void begin() override;
    void drawString(const std::string& text, const maths::vec3& position, const OFont& font, unsigned int color) override;
    void submit(const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder) override;
    void submit(const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder, float angle) override;
    void submit(const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder, const maths::vec2& dir) override;
    void end() override;
    void flush(OLayer2D* layer) override;

private:
    // Creates all the needed RenderBatches
    void createRenderBatches();

    // Generates our VAO and VBO
    void createVertexArray();

    // Sorts glyphs according to _sortType
    void sortGlyphs();

    // Comparator used by sortGlyphs()
    static bool compareFunction(Glyph* a, Glyph* b);


    GLuint m_VboID;
    GLuint m_VaoID;

    std::vector<Glyph*> m_GlyphPointers; ///< This is for sorting
    std::vector<Glyph> m_Glyphs; ///< These are the actual glyphs
    std::vector<RenderBatch> m_RenderBatches;

};
NS_O_END
