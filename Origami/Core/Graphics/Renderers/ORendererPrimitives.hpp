/****************************************************************************
 ORendererPrimitives.hpp
 
 Created by El Mehdi KHALLOUKI on 2/10/16.
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

#pragma once

#include <Core/Maths/OMaths.hpp>
#include <Core/OGL.hpp>
#include <Core/Graphics/OColorRGBA8.hpp>
#include <vector>

#include <Core/OMacros.hpp>
NS_O_BEGIN

class OCamera2D;

struct PrimitiveVertexData2D
{
    maths::vec2  m_Vertex;
    unsigned int m_Color;
};

class ORendererPrimitives {
    
    OColorRGBA8 m_Color;
public:
    ORendererPrimitives();
    ~ORendererPrimitives();
    
    void setDrawColor(float red, float green, float blue, float alpha);
    
    //Will draw a line depending on the camera MVP
    void drawLine(OCamera2D* camera, const maths::vec2& from, const maths::vec2& to);
    
    //will draw lines where :
    //x : from.x, y : from.y, z : to.x, w : to.y
    void drawLines(OCamera2D* camera, const std::vector<maths::vec4>& lines);
    
    void init();
private:
    // Generates our VAO and VBO
    void createVertexArray();
    
    GLuint m_VboID;
    GLuint m_VaoID;
    
    void getVertices(std::vector<PrimitiveVertexData2D>& vertices, const maths::vec2& from, const maths::vec2& to);
    void getVertices(std::vector<PrimitiveVertexData2D>& vertices, const std::vector<maths::vec4>& lines);
};

NS_O_END

