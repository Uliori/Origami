//
//  OSprite.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/21/15.
//
//

#pragma once

#include <Core/Utils/OGLUtils.hpp>
#include <Core/Maths/OMaths.hpp>
#include <Core/Graphics/OTexture.hpp>
#include <Core/Graphics/OColorRGBA8.hpp>
#include <Core/Graphics/Renderers/ORenderer2D.hpp>

#include <Core/OMacros.hpp>

NS_O_BEGIN

class ORenderer2D;
class OCamera2D;
class OSprite {
    
protected:
    maths::vec2 m_Size;
    maths::vec4 m_UV;
    
    float m_angle = 0;
    
    std::string m_TexturePath;
    OTexture* m_Texture = nullptr;
    
    maths::vec2  m_Position;
    OColorRGBA8  m_Color;
    float        m_zOrder;
    
    OSprite(){}

public:
    OSprite(float x, float y, float width, float height, const std::string& texturePath, float zOrder);
    virtual ~OSprite();

    float tag;
    bool hidden = false;

    //setters
    void setColor(const maths::vec4& color)
    {
        m_Color = color;
    }
    
    void moveBy(float x, float y)
    {
        m_Position += maths::vec2(x, y);
    }
    
    virtual void setPosition(const maths::vec2& position)
    {
        m_Position = position;
    }

    void setSize(const maths::vec2& size)
    {
        m_Size = size;
    }

    void setTexture(OTexture* texture)
    {
        m_Texture = texture;
    }

    void setUV(const maths::vec4& uv)
    {
        m_UV = uv;
    }
    
    void setAngle(float angle)
    {
        m_angle = angle;
    }
    
    //getters
    virtual const maths::vec2& getPosition()  { return m_Position;        }
    virtual float getAngle()                  { return m_angle;           }
    
    const maths::vec2& getSize() const        { return m_Size;            }
    const maths::vec4& getUV() const          { return m_UV;              }
    
    unsigned int getColor()                   { return m_Color.getColorUint();  }
    GLuint getTID() const                     { return m_Texture->textureID;    }
    float getZOrder() const                   { return m_zOrder;                }
    

    OTexture* getTexture() const { return m_Texture; }

    virtual void submit(ORenderer2D* renderer) ;
    virtual bool shouldBeRendered(OCamera2D* camera);

private:
    void setUVDefaults()
    {
        m_UV = maths::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }


};
NS_O_END
