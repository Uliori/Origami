//
//  OSprite.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/21/15.
//
//

#include "OSprite.h"
#include "Vertex2D.h"

#include <Core/Utils/OResourceManager.h>

NS_O_BEGIN

OSprite::OSprite(float x, float y, float width, float height, std::string texturePath, float zOrder)
:  m_Position(x, y), m_zOrder(zOrder), m_Size(width, height), m_Color(0xffffffff), m_TexturePath(texturePath)
// , m_VboID(0), m_VaoID(0)
{
    setUVDefaults();
    m_Texture = OResourceManager::textureCache()->loadTexture(m_TexturePath);
}

//OSprite::OSprite(float x, float y, float width, float height, OTexture *texture, float zOrder)
//:  m_Position(x, y),m_zOrder(zOrder), m_Size(width, height), m_vboID(0), m_vaoID(0), m_Color(0xffffffff), m_Texture(texture)
//{
//    setUVDefaults();
//}

OSprite::~OSprite()
{
//    if (m_vboID != 0) {
//        glDeleteBuffers(1, &m_vboID);
//    }
//
//    if (m_vaoID != 0) {
//        glDeleteVertexArrays(1, &m_vaoID);
//    }

    OResourceManager::textureCache()->releaseTexture(m_TexturePath);
}

//void OSprite::create()
//{
//    if (m_vaoID == 0) {
//        glGenVertexArrays(1, &m_vaoID);
//        glBindVertexArray(m_vaoID);
//    }
//    if (m_vboID == 0) {
//        glGenBuffers(1, &m_vboID);
//    }
//
//    VertexData2D data[6];
//
//
//    // first triangle
//    data[0].m_vertex =  maths::vec2(m_Position.x + m_Size.x, m_Position.y + m_Size.y);
//    data[0].m_uv     =  maths::vec2(1, 1);
//
//    data[1].m_vertex =  maths::vec2(m_Position.x         , m_Position.y + m_Size.y);
//    data[1].m_uv     =  maths::vec2(0, 1);
//
//    data[2].m_vertex =  maths::vec2(m_Position.x         , m_Position.y);
//    data[2].m_uv     =  maths::vec2(0, 0);
//
//    // second triangle
//    data[3].m_vertex =  maths::vec2(m_Position.x         , m_Position.y);
//    data[3].m_uv     =  maths::vec2(0, 0);
//
//    data[4].m_vertex =  maths::vec2(m_Position.x + m_Size.x, m_Position.y);
//    data[4].m_uv     =  maths::vec2(1, 0);
//
//    data[5].m_vertex =  maths::vec2(m_Position.x + m_Size.x, m_Position.y + m_Size.y);
//    data[5].m_uv     =  maths::vec2(1, 1);
//
//    for (int i = 0; i < 6; i++) {
//        data[i].m_color = 0xffffffff;
//    }
//
//    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glEnableVertexAttribArray(1);
//    glEnableVertexAttribArray(2);
//
//    glVertexAttribPointer(0, 2, GL_FLOAT,         GL_FALSE, sizeof(VertexData2D), (void *)offsetof(VertexData2D, m_vertex));
//    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE , sizeof(VertexData2D), (void *)offsetof(VertexData2D, m_color));
//    glVertexAttribPointer(2, 2, GL_FLOAT        , GL_FALSE, sizeof(VertexData2D), (void *)offsetof(VertexData2D, m_uv));
//
//    glBindVertexArray(0);
//
//}
//
//void OSprite::draw()
//{
//    glBindVertexArray(m_vaoID);
//
//    glDrawArrays(GL_TRIANGLES, 0, 6);
//
//    glBindVertexArray(0);
//}

NS_O_END
