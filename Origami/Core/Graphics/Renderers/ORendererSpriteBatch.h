//
//  ORendererSpriteBatch.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/24/15.
//
//

#pragma once 

#include <Core/OGL.h>

#include <Core/Graphics/Renderers/ORenderer2D.h>
#include <Core/Graphics/2D/Vertex2D.h>
#include <Core/Graphics/2D/OSprite.h>

#include <vector>

#include <Core/OMacros.h>

NS_O_BEGIN

class Glyph {
public:
    Glyph() {};
    Glyph(const maths::vec3 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color);
    
    GLuint textureID;
    
    VertexData2D topLeft;
    VertexData2D bottomLeft;
    VertexData2D topRight;
    VertexData2D bottomRight;
    
};

// Each render batch is used for a single draw call
class RenderBatch {
public:
    RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
    numVertices(NumVertices), texture(Texture) {
    }
    GLuint offset;
    GLuint numVertices;
    GLuint texture;
};


class ORendererSpriteBatch : public ORenderer2D
{
public:
    ORendererSpriteBatch();
    virtual ~ORendererSpriteBatch();
    
    void Init() override;
    void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE) override;
    void DrawString(const std::string& text, const maths::vec3& position, const OFont& font, unsigned int color) override;
    void Submit(const OSprite* renderable) override;
    void End() override;
    void Flush(OLayer2D *layer) override;
    
private:
    // Creates all the needed RenderBatches
    void createRenderBatches();
    
    // Generates our VAO and VBO
    void createVertexArray();
    
    // Sorts glyphs according to _sortType
    void sortGlyphs();
    
    // Comparators used by sortGlyphs()
    static bool compareFrontToBack(Glyph* a, Glyph* b);
    static bool compareBackToFront(Glyph* a, Glyph* b);
    static bool compareTexture(Glyph* a, Glyph* b);
    
    GLuint m_vboID;
    GLuint m_vaoID;
    
    GlyphSortType m_sortType;
    
    std::vector<Glyph*> m_glyphPointers; ///< This is for sorting
    std::vector<Glyph> m_glyphs; ///< These are the actual glyphs
    std::vector<RenderBatch> m_renderBatches;

};
NS_O_END
