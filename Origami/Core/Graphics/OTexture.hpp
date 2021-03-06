//
//  OTexture.h
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/22/15.
//
//

#pragma once

#include <Core/ORef.hpp>
#include <Core/OGL.hpp>

class OTexture : public ORef
{
public:
    GLuint textureID;
    GLint param_W_S;
    GLint param_W_T;

    OTexture():ORef() {}

    const float getScaledWidth() const
    {
        return m_Width;
    }

    const float getWidth() const
    {
        return m_Width / m_Scale;
    }

    const float getScaledHeight() const
    {
        return m_Height;
    }

    const float getHeight() const
    {
        return m_Height / m_Scale;
    }

    void setWidth (float w) { m_Width = w; }
    void setHeight(float h) { m_Height = h; }
    void setScale (float s) { m_Scale = s; if(m_Scale == 0) m_Scale = 1;}

private:
    float m_Width = 0;
    float m_Height = 0;
    float m_Scale = 1;
};
