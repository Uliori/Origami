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
#include <Core/Graphics/Renderers/ORendererFactory.hpp>

NS_O_BEGIN

OSprite::OSprite(float x, float y, float width, float height,const std::string& texturePath, float zOrder)
:  m_Position(x, y), m_zOrder(zOrder), m_Size(width, height), m_Color(), m_TexturePath(texturePath)
{
    setUVDefaults();
    m_Texture = OResourceManager::textureCache()->loadTexture(m_TexturePath);
}

OSprite::~OSprite()
{
    if (m_Texture) {
        OResourceManager::textureCache()->releaseTexture(m_TexturePath);
        m_Texture = nullptr;
    }
}

void OSprite::submit(ORenderer2D* renderer) 
{
    renderer->submitBox(ORendererFactory::OShader_Texture2D, getPosition(), getSize(), getUV(), m_Texture->textureID, m_Color.getColorUint(), getZOrder(), getAngle());
}

bool OSprite::shouldBeRendered(OCamera2D* camera)
{
    return camera->isBoxInView(m_Position, m_Size);
}
NS_O_END
