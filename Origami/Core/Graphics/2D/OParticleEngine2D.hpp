/****************************************************************************
 OParticleEngine2D.hpp
 
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

#include <Core/OMacros.h>
#include <vector>

NS_O_BEGIN

class OParticleBatch2D;
class ORenderer2D;

class OParticleEngine2D {
public:
    OParticleEngine2D();
    ~OParticleEngine2D();
    
    // After adding a particle batch, the ParticleEngine2D becomes
    // responsible for deallocation.
    void addParticleBatch(OParticleBatch2D* particleBatch);
    
    void update(float deltaTime);
    
    void draw(ORenderer2D* renderer);
    
private:
    std::vector<OParticleBatch2D*> m_Batches;
};


NS_O_END