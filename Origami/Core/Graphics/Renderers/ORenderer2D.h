//
//  ORenderer2D.h
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/15/15.
//
//

#pragma once

#include <Core/Maths/OMaths.h>

#include <Core/OMacros.h>

NS_O_BEGIN
    
class OLayer2D;
class OSprite;
class OFont;

enum class GlyphSortType {
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE
};

class ORenderer2D
{
protected:
    
    
public:
    virtual ~ORenderer2D() { }
    
    
    virtual void Init() {}
    virtual void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE) {}
    virtual void Submit(const OSprite* renderable) = 0;
    virtual void DrawString(const std::string& text, const maths::vec3& position, const OFont& font, const maths::vec4 &color) { }
    virtual void End() {}
    virtual void Flush(OLayer2D *layer) = 0;
};
    
NS_O_END