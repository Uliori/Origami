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
{
    setUVDefaults();
    m_Texture = OResourceManager::textureCache()->loadTexture(m_TexturePath);
}

OSprite::~OSprite()
{

    OResourceManager::textureCache()->releaseTexture(m_TexturePath);
}

void OSprite::submit(ORenderer2D* renderer) const
{
    renderer->submit(getPosition(), getSize(), getUV(), getTID(), getColor(), getZOrder());
}

NS_O_END
