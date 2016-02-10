/****************************************************************************
 OParticleEngine2D.cpp
 
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

#include "OParticleEngine2D.hpp"

#include <Core/Graphics/Renderers/ORenderer2D.hpp>
#include <Core/Graphics/2D/OParticleBatch2D.hpp>

NS_O_BEGIN

OParticleEngine2D::OParticleEngine2D() {
    // Empty
}

OParticleEngine2D::~OParticleEngine2D() {
    for (auto& b : m_Batches) {
        SAFE_DELETE(b);
    }
    m_Batches.clear();
}

void OParticleEngine2D::addParticleBatch(OParticleBatch2D* particleBatch) {
    m_Batches.push_back(particleBatch);
}

void OParticleEngine2D::update(float deltaTime) {
    for (auto& b : m_Batches) {
        b->update(deltaTime);
    }
}

void OParticleEngine2D::draw(ORenderer2D* renderer){
    for (auto& b : m_Batches) {
        b->draw(renderer);
    }
}



NS_O_END