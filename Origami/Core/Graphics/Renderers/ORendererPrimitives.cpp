/****************************************************************************
 ORendererPrimitives.cpp
 
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

#include "ORendererPrimitives.hpp"
#include <Core/Graphics/2D/OCamera2D.hpp>
#include <Core/Graphics/Renderers/ORendererFactory.hpp>
NS_O_BEGIN

ORendererPrimitives::ORendererPrimitives()
: m_Color(OColorRGBA8()), m_VboID(0), m_VaoID(0)
{
    
}

ORendererPrimitives::~ORendererPrimitives()
{
    if (m_VboID != 0) {
        glDeleteBuffers(1, &m_VboID);
    }
    
    if (m_VaoID != 0) {
        glDeleteVertexArrays(1, &m_VaoID);
    }
}

void ORendererPrimitives::init()
{
    createVertexArray();
}

void ORendererPrimitives::setDrawColor(float red, float green, float blue, float alpha)
{
    m_Color.setColor(red, green, blue, alpha);
}

void ORendererPrimitives::drawLine(OCamera2D* camera, const maths::vec2& from, const maths::vec2& to)
{
    //create a list of vertices to render
    std::vector <PrimitiveVertexData2D> vertices;
    getVertices(vertices, from, to);
    
    ORendererFactory::OShader_Color2D->bind();
    ORendererFactory::OShader_Color2D->setUniformMat4("u_MVP", camera->getCameraMatrix());

    glDrawArrays(GL_LINES, 0, 2);
    
    ORendererFactory::OShader_Color2D->unbind();
    glBindVertexArray(0);

}

void ORendererPrimitives::drawLines(OCamera2D* camera, const std::vector<maths::vec4>& lines)
{
    //create a list of vertices to render
    std::vector <PrimitiveVertexData2D> vertices;
    getVertices(vertices, lines);
    
    ORendererFactory::OShader_Color2D->bind();
    ORendererFactory::OShader_Color2D->setUniformMat4("u_MVP", camera->getCameraMatrix());
    
    glDrawArrays(GL_LINES, 0, (int)vertices.size());
    
    ORendererFactory::OShader_Color2D->unbind();
    glBindVertexArray(0);
}



void ORendererPrimitives::createVertexArray()
{
    // Generate the VAO if it isn't already generated
    if (m_VaoID == 0) {
        glGenVertexArrays(1, &m_VaoID);
    }
    
    // Bind the VAO. All subsequent opengl calls will modify it's state.
    glBindVertexArray(m_VaoID);
    
    //G enerate the VBO if it isn't already generated
    if (m_VboID == 0) {
        glGenBuffers(1, &m_VboID);
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
    
    //Tell opengl what attribute arrays we need
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(0, 2, GL_FLOAT,         GL_FALSE, sizeof(PrimitiveVertexData2D), (void *)offsetof(PrimitiveVertexData2D, m_Vertex));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE , sizeof(PrimitiveVertexData2D), (void *)offsetof(PrimitiveVertexData2D, m_Color));
    
    glBindVertexArray(0);

}


void ORendererPrimitives::getVertices(std::vector<PrimitiveVertexData2D>& vertices, const maths::vec2& from, const maths::vec2& to)
{
    vertices.clear();
    vertices.resize(2);
    
    vertices[0].m_Vertex = from;
    vertices[0].m_Color = m_Color.getColorUint();
    vertices[1].m_Vertex = to;
    vertices[1].m_Color = m_Color.getColorUint();
    
    glBindVertexArray(m_VaoID);
    // Bind our VBO
//    glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
    // Orphan the buffer (for speed)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PrimitiveVertexData2D), NULL, GL_DYNAMIC_DRAW);
    // Upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(PrimitiveVertexData2D), vertices.data());
    
}

void ORendererPrimitives::getVertices(std::vector<PrimitiveVertexData2D>& vertices, const std::vector<maths::vec4>& lines)
{
    vertices.clear();
    vertices.resize(lines.size() * 2);
    
    for (int i = 0; i < lines.size(); i++) {
        vertices[2 * i].m_Vertex     = maths::vec2(lines[i].x, lines[i].y);
        vertices[2 * i].m_Color      = m_Color.getColorUint();
        vertices[2 * i + 1].m_Vertex = maths::vec2(lines[i].z, lines[i].w);
        vertices[2 * i + 1].m_Color  = m_Color.getColorUint();
    }
    
    glBindVertexArray(m_VaoID);
    // Bind our VBO
//    glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
    // Orphan the buffer (for speed)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PrimitiveVertexData2D), NULL, GL_DYNAMIC_DRAW);
    // Upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(PrimitiveVertexData2D), vertices.data());
}

NS_O_END