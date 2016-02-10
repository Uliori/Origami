//
//  ORenderer2D.h
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/15/15.
//
//

#pragma once

#include <string>

#include <Core/Maths/OMaths.hpp>
#include <Core/OMacros.hpp>
#include <Core/OGL.hpp>

NS_O_BEGIN

class OLayer2D;
class OSprite;
class OFont;

class ORenderer2D
{
public:
    virtual ~ORenderer2D() { }

    virtual void init() {}
    virtual void begin() {}
    virtual void submit(const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder) = 0;
    virtual void submit(const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder, float angle) {};
    virtual void submit(const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder, const maths::vec2& dir) {};
    virtual void drawString(const std::string& text, const maths::vec3& position, const OFont& font, unsigned int color) { }
    virtual void end() {}
    virtual void flush(OLayer2D* layer) = 0;
};

NS_O_END
