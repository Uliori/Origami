//
//  Vertex2D.h
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/21/15.
//
//

#pragma once

#include <Core/Maths/OMaths.h>

namespace Origami {
    
    struct VertexData2D
    {
        maths::vec3  m_vertex;
        maths::vec2  m_uv;
        unsigned int m_color;
		unsigned int m_tid;
        
        
        void setColor(unsigned int color) { m_color = color; }
        void setColor(const maths::vec4& color)
        {
            uint r = (uint)(color.x * 255.0f);
            uint g = (uint)(color.y * 255.0f);
            uint b = (uint)(color.z * 255.0f);
            uint a = (uint)(color.w * 255.0f);
            
            m_color = a << 24 | b << 16 | g << 8 | r;
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
}

