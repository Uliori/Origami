/****************************************************************************
 ParticlesScene.cpp
 
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

#include "ParticlesScene.hpp"


#include <Core/Utils/OResourceManager.h>
#include <Core/Inputs/OInputsManager.h>
#include <Core/Graphics/2D/OParticleBach2D.hpp>

ParticlesScene::ParticlesScene() : OScene()
{
    
}

void ParticlesScene::create()
{
    OScene::create();
    
    
    OSize frameSize = ODirector::director()->getVirtualSize();
    
    //sky
    sky = new OSprite(0, 0, frameSize.width, frameSize.height, "psky.png", 0);
    addSprite(sky);
    
    particles = new OParticleBatch2D();
    particles->setShouldOverride(false);
    
    particles->init(60, .9f , "particle.png", 1,
                    [](OParticleBatch2D* batch, float deltaTime){
                        OSize frameSize = ODirector::director()->getVirtualSize();
                        vec2 posi = vec2(fRand(0, frameSize.width), fRand(-frameSize.height/2, 0));
                        batch->addParticle(posi, vec2(fRand(-10, 10), fRand(20, 40)), OColorRGBA8(0, 0, 0, 1), 5);
                    },
                    [](OParticle2D& particle, float deltaTime){
                        particle.position += particle.velocity * deltaTime;
                        
                        if (particle.position.y > ODirector::director()->getVirtualSize().height + particle.width
                            || particle.position.x < -particle.width
                            || particle.position.x > ODirector::director()->getVirtualSize().width + particle.width) {
                            particle.life = 0.0f;
                        }
                        else
                        {
                            particle.life = 1.0f;
                        }
                    });
    getMainLayer2D()->particleEngine->addParticleBatch(particles);
}

void ParticlesScene::onResize()
{
    
    OSize frameSize = ODirector::director()->getVirtualSize();
    
    sky->setSize(vec2(frameSize.width, frameSize.height));
}

ParticlesScene::~ParticlesScene()
{
    
}