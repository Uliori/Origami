//
//  ORenderer2D.h
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/15/15.
//
//

#pragma once

#include <string>

#include <Core/Maths/OMaths.h>
#include <Core/OMacros.h>

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
    virtual void submit(const OSprite* renderable) = 0;
    virtual void drawString(const std::string& text, const maths::vec3& position, const OFont& font, unsigned int color) { }
    virtual void end() {}
    virtual void flush(OLayer2D *layer) = 0;
};

NS_O_END
