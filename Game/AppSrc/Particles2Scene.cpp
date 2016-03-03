/****************************************************************************
 Particles2Scene.cpp
 
 Created by El Mehdi KHALLOUKI on 1/17/16.
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

#include "Particles2Scene.hpp"

Particles2Scene::Particles2Scene() : OScene()
{
    
}

void Particles2Scene::onCreate()
{
    particles = new OParticleBatch2D();
    
//    OSize frameSize = ODirector::director()->getVirtualSize();
//    back = new OSprite(0, 0, frameSize.width, frameSize.height, "psky2.png", 0);
//    addSprite(back);
    
    OSize frameSize = ODirector::director()->getVirtualSize();
    
    
    particles->init(150, .25f , "particle3.png", 1,
                    [](OParticleBatch2D* batch, float deltaTime){
                        OSize frameSize = ODirector::director()->getVirtualSize();
                        float vrand = fRand(-100, 100);
                        vec2 velocity = (vec2(frameSize.width, frameSize.height) / fRand(2.5f, 3.f));
                        float pwidth = 50;
                        batch->addParticle(vec2(vrand - pwidth, -10 - pwidth) , velocity, OColorRGBA8(1, 0, 0, 1), pwidth);
                    },
                    [](OParticle2D& particle, float deltaTime){
                        particle.position += particle.velocity * deltaTime;
                        const maths::vec3 startColor = maths::vec3(1, 0, 0);
                        const maths::vec3 endColor   = maths::vec3(0, 0, 1);
                        
                        maths::vec3 pColor = (endColor - startColor) * (1 - particle.life) + startColor;
                        particle.color = maths::vec4(pColor, 1);
                        
                    });
    getMainLayer2D()->particleEngine->addParticleBatch(particles);
    
}

void Particles2Scene::onClear()
{
    
}

void Particles2Scene::onResize()
{
//    OSize frameSize = ODirector::director()->getVirtualSize();
//    back->setSize(maths::vec2(frameSize.width, frameSize.height));
    
    OSize frameSize = ODirector::director()->getVirtualSize();
    
}

Particles2Scene::~Particles2Scene()
{
    
}