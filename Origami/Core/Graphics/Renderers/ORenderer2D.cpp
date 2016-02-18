/****************************************************************************
ORenderer2D.cpp

 Created by El Mehdi KHALLOUKI on 2/17/16.
 Copyright (c) 2016 __MyCompanyName__.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

****************************************************************************/

#include "ORenderer2D.hpp"

NS_O_BEGIN

//Glyph
Glyph::Glyph(const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder)
:textureID(texture), a_zOrder(zOrder) {
    
    topLeft.setColor(color);
    topLeft.setPosition(position.x, position.y + dimensions.y);
    topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
    
    bottomLeft.setColor(color);
    bottomLeft.setPosition(position.x, position.y);
    bottomLeft.setUV(uvRect.x, uvRect.y);
    
    bottomRight.setColor(color);
    bottomRight.setPosition(position.x + dimensions.x, position.y);
    bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
    
    topRight.setColor(color);
    topRight.setPosition(position.x + dimensions.x, position.y + dimensions.y);
    topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
}

Glyph::Glyph(const maths::vec2 &position, const maths::vec2 &dimensions, const maths::vec4 &uvRect, GLuint texture, unsigned int color, float zOrder, float angle)
:textureID(texture), a_zOrder(zOrder) {
    
    maths::vec2 halfDims(dimensions.x * 0.5f, dimensions.y * 0.5f);
    
    // Get points centered at origin
    maths::vec2 tl(-halfDims.x, halfDims.y);
    maths::vec2 bl(-halfDims.x, -halfDims.y);
    maths::vec2 br(halfDims.x, -halfDims.y);
    maths::vec2 tr(halfDims.x, halfDims.y);
    
    // Rotate the points
    tl = rotatePoint(tl, angle) + halfDims;
    bl = rotatePoint(bl, angle) + halfDims;
    br = rotatePoint(br, angle) + halfDims;
    tr = rotatePoint(tr, angle) + halfDims;
    
    topLeft.setColor(color);
    topLeft.setPosition(position.x + tl.x, position.y + tl.y);
    topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
    
    bottomLeft.setColor(color);
    bottomLeft.setPosition(position.x + bl.x, position.y + bl.y);
    bottomLeft.setUV(uvRect.x, uvRect.y);
    
    bottomRight.setColor(color);
    bottomRight.setPosition(position.x + br.x, position.y + br.y);
    bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
    
    topRight.setColor(color);
    topRight.setPosition(position.x + tr.x, position.y + tr.y);
    topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
}

Glyph::Glyph(const VertexData2D &atopLeft,const VertexData2D &abottomLeft,const VertexData2D &atopRight,const VertexData2D &abottomRight, GLuint texture, float zOrder)
:a_zOrder(zOrder), textureID(texture)
{
    topLeft = atopLeft;
    topRight = atopRight;
    bottomLeft = abottomLeft;
    bottomRight = abottomRight;
}


maths::vec2 Glyph::rotatePoint(const maths::vec2& pos, float angle)
{
    maths::vec2 newv;
    newv.x = pos.x * cos(angle) - pos.y * sin(angle);
    newv.y = pos.x * sin(angle) + pos.y * cos(angle);
    return newv;
}


NS_O_END
