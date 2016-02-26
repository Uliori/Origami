/****************************************************************************
 OB2DSprite.cpp
 
 Created by El Mehdi KHALLOUKI on 2/15/16.
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

#include "OB2DSprite.hpp"
#include <Core/Graphics/Renderers/ORendererFactory.hpp>

NS_O_BEGIN

OB2DSprite::OB2DSprite(b2World* world, const maths::vec2& position, const maths::vec2& dimensions, const std::string& texturePath, float zOrder,
           bool fixedRotation, bool isDynamic, float angle)
:OSprite(position.x, position.y, dimensions.x, dimensions.y, texturePath, zOrder),
m_FixedRotation(fixedRotation), m_IsDynamic(isDynamic)
{
    setAngle(angle);
    
    b2BodyDef bodyDef;
    if (m_IsDynamic) {
        bodyDef.type = b2_dynamicBody;
    }
    else {
        bodyDef.type = b2_staticBody;
    }
    bodyDef.position.Set(m_Position.x / O_PTM_RATIO, m_Position.y / O_PTM_RATIO);
    bodyDef.fixedRotation = m_FixedRotation;
    bodyDef.angle = m_angle;
    m_Body = world->CreateBody(&bodyDef);
    
    //Will create the shape and the fixture
    createFixture();
    
}

void OB2DSprite::createFixture()
{
    b2CircleShape circleShape;
    circleShape.m_radius = 20 / O_PTM_RATIO;
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
//    fixtureDef.friction = 0.3f;
    m_Fixture = m_Body->CreateFixture(&fixtureDef);
}

void OB2DSprite::destroy(b2World *world)
{
    if (m_Body) {
        world->DestroyBody(m_Body);
        m_Body = nullptr;
    }
}

OB2DSprite::~OB2DSprite()
{
    
}

void OB2DSprite::submit(ORenderer2D* renderer)
{
    renderer->submitBox(ORendererFactory::OShader_Texture2D, getPosition() - (m_Size / 2), getSize(), getUV(), m_Texture->textureID, m_Color.getColorUint(), getZOrder(), getAngle());
}

NS_O_END