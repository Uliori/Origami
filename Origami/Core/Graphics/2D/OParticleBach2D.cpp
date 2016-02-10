/****************************************************************************
 OParticleBach2D.cpp

 Created by El Mehdi KHALLOUKI on 1/15/16.
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

#include "OParticleBatch2D.hpp"
#include <Core/Utils/OResourceManager.hpp>

NS_O_BEGIN

OParticleBatch2D::OParticleBatch2D() {
  m_DecayRate         = 0.1f;
  m_ZOrder            = 0.0f;
  m_Particles.clear();
  m_MaxParticles        = 0;
  m_LastFreeParticle    = 0;
  m_Texture       = nullptr;
}

OParticleBatch2D::~OParticleBatch2D() {
    m_Particles.clear();
    OResourceManager::textureCache()->releaseTexture(m_TexturePath);
    m_Texture = nullptr;
}

void OParticleBatch2D::init(int maxParticles,
                            float decayRate,
                            std::string texturePath,
                            float depth,
                            std::function<void(OParticleBatch2D*, float)> respawnFunc,
                            std::function<void(OParticle2D&, float)> updateFunc /* = defaultParticleUpdate */) {
    m_MaxParticles = maxParticles;
    
    m_Particles.clear();
    m_Particles.resize(m_MaxParticles, OParticle2D());
//    for (unsigned int i = 0; i < m_MaxParticles; ++i)
//        m_Particles.push_back(OParticle2D());

    m_DecayRate = decayRate;
    m_TexturePath = texturePath;
    m_UpdateFunc = updateFunc;
    m_RespawnFunc = respawnFunc;
    m_ZOrder = depth;

    m_Texture = OResourceManager::textureCache()->loadTexture(m_TexturePath);
}

void OParticleBatch2D::update(float deltaTime) {
    
    m_RespawnFunc(this, deltaTime);
    for (int i = 0; i < m_MaxParticles; i++) {
        // Check if it is active
        auto& p = m_Particles[i];
        if (p.life > 0.0f) {
            // Update using function pointer
            m_UpdateFunc(p, deltaTime);
            p.life -= m_DecayRate * deltaTime;
        }
    }
}

void OParticleBatch2D::draw(ORenderer2D* renderer) {
    maths::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    for (int i = 0; i < m_MaxParticles; i++) {
        auto& p = m_Particles[i];
        if (p.life > 0.0f) {
            renderer->submit(p.position, maths::vec2(p.width, p.width), uvRect, m_Texture->textureID, p.color.getColorUint(), m_ZOrder);
        }
    }
}

void OParticleBatch2D::addParticle(const maths::vec2& position,
                                   const maths::vec2& velocity,
                                   const OColorRGBA8& color,
                                   float width) {
    int particleIndex = findFreeParticle();
    if (particleIndex == -1) {
        return;
    }
    
    auto& p = m_Particles[particleIndex];
    p.life = 1.0f;
    p.position = position;
    p.velocity = velocity;
    p.color = color;
    p.width = width;

}

int OParticleBatch2D::findFreeParticle() {

    for (int i = m_LastFreeParticle; i < m_MaxParticles; i++) {
        if (m_Particles[i].life <= 0.0f) {
            m_LastFreeParticle = i;
            return i;
        }
    }

    for (int i = 0; i < m_LastFreeParticle; i++) {
        if (m_Particles[i].life <= 0.0f) {
            m_LastFreeParticle = i;
            return i;
        }
    }

    
    // No particles are free, overwrite first particle
    if (m_ShouldOverride) {
        return 0;
    }
    return -1;
}


NS_O_END
