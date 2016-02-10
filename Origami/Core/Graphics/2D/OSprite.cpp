//
//  OSprite.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/21/15.
//
//

#include "OSprite.hpp"
#include "Vertex2D.hpp"

#include <Core/Utils/OResourceManager.hpp>

NS_O_BEGIN

OSprite::OSprite(float x, float y, float width, float height, std::string texturePath, float zOrder)
:  m_Position(x, y), m_zOrder(zOrder), m_Size(width, height), m_Color(), m_TexturePath(texturePath)
{
    setUVDefaults();
    m_Texture = OResourceManager::textureCache()->loadTexture(m_TexturePath);
}

OSprite::~OSprite()
{
    OResourceManager::textureCache()->releaseTexture(m_TexturePath);
    m_Texture = nullptr;
}

void OSprite::submit(ORenderer2D* renderer) 
{
    renderer->submit(m_Position, m_Size, m_UV, m_Texture->textureID, m_Color.getColorUint(), m_zOrder, m_angle);
}

bool OSprite::shouldBeRendered(OCamera2D* camera)
{
    return camera->isBoxInView(m_Position, m_Size);
}
NS_O_END
