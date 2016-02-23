/****************************************************************************
 OB2DSprite.hpp
 
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

#pragma once

#include <Core/Physics/2D/O2DPhysics.hpp>

#include <Core/OMacros.hpp>
#include <Core/Graphics/2D/OSprite.hpp>
NS_O_BEGIN

class OB2DSprite : public OSprite {
    
    b2Body* m_Body          = nullptr;
    b2Fixture *m_Fixture    = nullptr;
    
    bool m_IsDynamic;
    bool m_FixedRotation;
public:
    OB2DSprite(b2World* world, const maths::vec2& position, const maths::vec2& dimensions, const std::string& texturePath, float zOrder,
               bool fixedRotation, bool isDynamic, float angle = 0.0f);
    ~OB2DSprite();
    
    void destroy(b2World *world);
    virtual void createFixture();
    
    b2Body*                    getBody()          const { return m_Body; }
    b2Fixture*                 getFixture()       const { return m_Fixture; }
    
    inline void setPosition(const maths::vec2& position) override
    {
        if (m_Body)
            m_Body->SetTransform(b2Vec2(position.x / O_PTM_RATIO, position.y / O_PTM_RATIO), 0);
    }
    
    inline maths::vec2& getPosition() override
    {
        OSprite::setPosition(maths::vec2(m_Body->GetPosition().x * O_PTM_RATIO, m_Body->GetPosition().y * O_PTM_RATIO));
        return  m_Position;
    }
    
//    inline float getAngle() override{ return m_Body->GetAngle(); }
    const bool& getFixedRotation() const { return m_FixedRotation; }
    const bool& getIsDynamic()     const { return m_IsDynamic; }
    
    void submit(ORenderer2D* renderer) override;
};
NS_O_END