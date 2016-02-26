//
//  ORenderer2D.h
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/15/15.
//
//

#pragma once

#include <string>
#include <vector>

#include <Core/Maths/OMaths.hpp>
#include <Core/OMacros.hpp>
#include <Core/OGL.hpp>
#include <Core/Graphics/Shaders/OShader.hpp>
#include <Core/Graphics/2D/Vertex2D.hpp>

NS_O_BEGIN

class OLayer2D;
class OSprite;
class OFont;

// Each render batch is used for a single draw call
class RenderBatch {
public:
    RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture, OShader *shader)
    :offset(Offset),numVertices(NumVertices), texture(Texture), currentShader(shader) {}
    GLuint offset = 0;
    GLuint numVertices = 0;
    GLuint texture = 0;
    OShader *currentShader;
};


class Glyph {
public:
    Glyph() {};
    Glyph(OShader *shader, const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder);
    Glyph(OShader *shader, const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder, float angle);
    Glyph(OShader *shader, const VertexData2D &atopLeft, const VertexData2D &abottomLeft, const VertexData2D &atopRight, const VertexData2D &abottomRight, GLuint texture, float zOrder);
    
    GLuint textureID = 0;
    OShader *currentShader = nullptr;
    
    VertexData2D topLeft;
    VertexData2D bottomLeft;
    VertexData2D topRight;
    VertexData2D bottomRight;
    
    float a_zOrder = 0;
    
    
private:
    maths::vec2 rotatePoint(const maths::vec2& pos, float angle);
};

class ORenderer2D
{
public:
    virtual ~ORenderer2D() { }

    virtual void init() {}
    virtual void begin() {}
    
    virtual void submitPolygon(const std::vector<Glyph>& glyphs) {};
    
    virtual void submitBox(OShader *shader, const VertexData2D &atopLeft,const VertexData2D &abottomLeft,const VertexData2D &atopRight,const VertexData2D &abottomRight, GLuint texture, float zOrder) {}
    virtual void submitBox(OShader *shader, const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder) {}
    virtual void submitBox(OShader *shader, const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder, float angle) {}
    virtual void submitBox(OShader *shader, const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder, const maths::vec2& dir) {}
    virtual void drawString(OShader *shader, const std::string& text, const maths::vec3& position, const OFont& font, unsigned int color, float zOrder) {}
    
    virtual void end() {}
    
    virtual void flush(OLayer2D* layer) {}
};

NS_O_END
