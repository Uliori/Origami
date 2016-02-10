//
//  OSprite.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/21/15.
//
//

#pragma once

#include <Core/Utils/OGLUtils.h>
#include <Core/Maths/OMaths.h>
#include <Core/Graphics/OTexture.h>
#include <Core/Graphics/OColorRGBA8.h>
#include <Core/Graphics/Renderers/ORenderer2D.h>

#include <Core/OMacros.h>

NS_O_BEGIN

class ORenderer2D;
class OSprite {
private:
    maths::vec2 m_Size;
    maths::vec4 m_UV;

    std::string m_TexturePath;
    OTexture* m_Texture = nullptr;

    float m_angle = 0;
protected:
    maths::vec2  m_Position;
    OColorRGBA8  m_Color;
    float        m_zOrder;
    OSprite(){}

public:
    OSprite(float x, float y, float width, float height, std::string texturePath, float zOrder);
    ~OSprite();

    float tag;
    bool hidden = false;

    //setters
    inline void setColor(const maths::vec4& color)
    {
        m_Color = color;
    }
    
    inline void setPosition(const maths::vec2& position)
    {
        m_Position = position;
    }

    inline void setSize(const maths::vec2& size)
    {
        m_Size = size;
    }

    inline void setTexture(OTexture* texture)
    {
        m_Texture = texture;
    }

    inline void setUV(const maths::vec4& uv)
    {
        m_UV = uv;
    }
    
    inline void setAngle(float angle)
    {
        m_angle = angle;
    }
    
    //getters
    inline const maths::vec2& getPosition() const { return m_Position; }
    inline const maths::vec2& getSize() const { return m_Size; }
    inline const unsigned int getColor()  { return m_Color.getColorUint(); }
    inline const maths::vec4& getUV() const { return m_UV; }
    inline const GLuint getTID() const { return m_Texture->textureID; }
    inline const float getZOrder() const { return m_zOrder; }
    inline const float getAngle() const { return m_angle; }

    inline OTexture* getTexture() const { return m_Texture; }

    virtual void submit(ORenderer2D* renderer) ;

private:
    void setUVDefaults()
    {
        m_UV = maths::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }


};
NS_O_END
