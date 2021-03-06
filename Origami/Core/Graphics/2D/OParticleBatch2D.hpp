/****************************************************************************
 OParticleBach2D.hpp

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

#pragma once

#include <functional>
#include <vector>

#include <Core/OMacros.hpp>
#include <Core/OTypes.hpp>
#include <Core/Graphics/OTexture.hpp>
#include <Core/Graphics/OColorRGBA8.hpp>
#include <Core/Graphics/Renderers/ORenderer2D.hpp>

#include <Core/Maths/OMaths.hpp>

NS_O_BEGIN

class OParticle2D {
public:
    maths::vec2 position = maths::vec2();
    maths::vec2 velocity = maths::vec2();
    OColorRGBA8 color    = OColorRGBA8();
    float life = 0.0f;
    float width = 0.0f;
};

// Default function pointer
inline void defaultParticleUpdate(OParticle2D& particle, float deltaTime) {
    particle.position += particle.velocity * deltaTime;
}

class OParticleBatch2D {    
public:
    OParticleBatch2D();
    ~OParticleBatch2D();

    void init(int maxParticles,
              float decayRate,
              std::string texturePath,
              float depth,
              std::function<void(OParticleBatch2D*, float)> respawnFunc,
              std::function<void(OParticle2D&, float)> updateFunc = defaultParticleUpdate);

    void update(float deltaTime);

    void draw(ORenderer2D* renderer);

    void addParticle(const maths::vec2& position,
                     const maths::vec2& velocity,
                     const OColorRGBA8& color,
                     float width);

    inline void setShouldOverride(bool soverride) { m_ShouldOverride = soverride; }
    
private:
    int findFreeParticle();

    std::function<void(OParticle2D&, float)> m_UpdateFunc;///< Function pointer for custom updates
    std::function<void(OParticleBatch2D*, float)> m_RespawnFunc;///< Function pointer for custom respawn
    
    float m_DecayRate         = 0.1f;
    float m_ZOrder            = 0.0f;

    int m_MaxParticles        = 0;
    int m_LastFreeParticle    = 0;
    OTexture* m_Texture       = nullptr;

    std::string m_TexturePath;
    std::vector<OParticle2D> m_Particles;

    //should override the first particle if no particle is available
    bool m_ShouldOverride     = true;

};

NS_O_END
