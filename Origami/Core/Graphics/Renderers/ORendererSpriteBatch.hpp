//
//  ORendererSpriteBatch.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/24/15.
//
//

#pragma once


#include <Core/Graphics/Renderers/ORenderer2D.hpp>
#include <Core/Graphics/2D/OSprite.hpp>

#include <vector>

#include <Core/OMacros.hpp>

NS_O_BEGIN


class ORendererSpriteBatch : public ORenderer2D
{
    enum OTextAlignment
    {
        OTEXT_ALIGN_LEFT = 1,
        OTEXT_ALIGN_CENTERED_H = 2,
        OTEXT_ALIGN_RIGHT = 4,
        OTEXT_ALIGN_TOP = 8,
        OTEXT_ALIGN_CENTERED_V = 16,
        OTEXT_ALIGN_BOTTOM = 32
    };
    
public:
    ORendererSpriteBatch();
    virtual ~ORendererSpriteBatch();

    void init() override;
    void begin() override;
    
    void drawString(OShader *shader, const std::vector<std::string>& Lines, const std::vector<float>& LinesLength, const Rect& rect, int alignment, const OFont& font, unsigned int color, float zOrder) override;
    
    void submitBox(OShader *shader, const VertexData2D &atopLeft,const VertexData2D &abottomLeft,const VertexData2D &atopRight,const VertexData2D &abottomRight, GLuint texture, float zOrder) override;
    void submitBox(OShader *shader, const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder) override;
    void submitBox(OShader *shader, const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder, float angle) override;
    void submitBox(OShader *shader, const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder, const maths::vec2& dir) override;
    
    void submitPolygon(const std::vector<Glyph>& glyphs) override;
    
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
