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
    maths::vec3  m_vertex;
    maths::vec2  m_uv;
    maths::vec4  m_color;
    unsigned int m_tid;
    
    
    void setColor(maths::vec4 color) { m_color = color; }
    void setColor(float r, float g, float b, float a)
    {
        m_color = maths::vec4(r, g, b, a);
    }
    
    void setPosition(float x, float y, float z)
    {
        m_vertex = maths::vec3(x, y, z);
    }
    
    void setPosition(const maths::vec3& position)
    {
        m_vertex = position;
    }
    
    
    void setTexture(GLuint texture)
    {
        m_tid = texture;
    }
    
    void setUV(float u, float v)
    {
        m_uv = maths::vec2(u, v);
    }
    
    void setUV(const maths::vec2& uv)
    {
        m_uv = uv;
    }

};
NS_O_END

