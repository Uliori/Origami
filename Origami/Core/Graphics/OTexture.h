//
//  OTexture.h
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/22/15.
//
//

#pragma once

#include <Core/OGL.h>

struct OTexture
{
    GLuint textureID;
    
    float getScaledWidth()
    {
        return width;
    }
    
    float getWidth()
    {
        return width / scale;
    }
    
    float getScaledHeight()
    {
        return height;
    }
    
    float getHeight()
    {
        return height / scale;
    }
    
    
    void setWidth (float w) { width = w; }
    void setHeight(float h) { height = h; }
    void setScale (float s) { scale = s; if(scale == 0) scale = 1;}
    
private:
    float width;
    float height;
    float scale;
};
