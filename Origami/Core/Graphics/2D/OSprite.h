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
#include <Core/Graphics/Renderers/ORenderer2D.h>

#include <Core/OMacros.h>

NS_O_BEGIN

class ORenderer2D;
class OSprite {
private:
    maths::vec2 m_Size;
    maths::vec4 m_UV;

    GLuint m_VaoID;
    GLuint m_VboID;

    std::string m_TexturePath;
    OTexture *m_Texture;

protected:
    maths::vec2  m_Position;
    unsigned int m_Color;
    float        m_zOrder;
    OSprite(){}
public:
    OSprite(float x, float y, float width, float height, std::string texturePath, float zOrder);
//    OSprite(float x, float y, float width, float height, OTexture *texture, float zOrder);
    ~OSprite();

    float tag;

//    void create();
//    void draw();

    //setters
    inline void setColor(unsigned int color) { m_Color = color; }
    inline void setColor(const maths::vec4& color)
    {
        uint r = (uint)(color.x * 255.0f);
        uint g = (uint)(color.y * 255.0f);
        uint b = (uint)(color.z * 255.0f);
        uint a = (uint)(color.w * 255.0f);

        m_Color = a << 24 | b << 16 | g << 8 | r;
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

    //getters
    inline const maths::vec2& getPosition() const { return m_Position; }
    inline const maths::vec2& getSize() const { return m_Size; }
    inline const unsigned int getColor() const { return m_Color; }
    inline const maths::vec4& getUV() const { return m_UV; }
    inline const GLuint getTID() const { return m_Texture->textureID; }
    inline const GLuint getZOrder() const { return m_zOrder; }

    inline OTexture* getTexture() const { return m_Texture; }

    virtual void submit(ORenderer2D* renderer) const
    {
        renderer->submit(this);
    }

private:
    void setUVDefaults()
    {
        m_UV = maths::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }


};
NS_O_END
