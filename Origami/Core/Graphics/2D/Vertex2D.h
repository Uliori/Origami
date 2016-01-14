//
//  Vertex2D.h
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/21/15.
//
//

#pragma once

#include <Core/Maths/OMaths.h>
#include <Core/Utils/OGLUtils.h>

#include <Core/OMacros.h>

NS_O_BEGIN

struct VertexData2D
{
    maths::vec2  m_Vertex;
    maths::vec2  m_UV;
    unsigned int m_Color;
    unsigned int m_TID;
    float        m_zOrder;

    void setColor(unsigned int color) { m_Color = color; }
    void setColor(const maths::vec4& color)
    {
        uint r = (uint)(color.x * 255.0f);
        uint g = (uint)(color.y * 255.0f);
        uint b = (uint)(color.z * 255.0f);
        uint a = (uint)(color.w * 255.0f);

        m_Color = a << 24 | b << 16 | g << 8 | r;
    }

    void setPosition(float x, float y)
    {
        m_Vertex = maths::vec2(x, y);
    }

    void setPosition(float x, float y, float z)
    {
        m_Vertex = maths::vec2(x, y);
        m_zOrder = z;
    }

    void setPosition(const maths::vec2& position)
    {
        m_Vertex = position;
    }


    void setTexture(GLuint texture)
    {
        m_TID = texture;
    }

    void setUV(float u, float v)
    {
        m_UV = maths::vec2(u, v);
    }

    void setUV(const maths::vec2& uv)
    {
        m_UV = uv;
    }

};
NS_O_END
