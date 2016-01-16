/****************************************************************************
 BambooScene.cpp
 
 Created by El Mehdi KHALLOUKI on 1/14/16.
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

#include "BambooScene.hpp"
#include <Core/Inputs/OInputsManager.h>

BambooScene::BambooScene()
{
    
}

BambooScene::~BambooScene()
{
    
}

void BambooScene::create()
{
    OScene::create();
    
    OSize frameSize = ODirector::director()->getVirtualSize();
    
    //sky
    sky = new OSprite(0, 0, frameSize.width, frameSize.height, "bsky.png", 0);
    addSprite(sky);
    
    particles = new OParticleBatch2D();
//    particles->init(1000, 1.0f , "cloud.png", 5); //For default particles update method
    particles->init(1000, 1.0f , "cloud.png", 5, [](OParticle2D& particle, float deltaTime){
        particle.position += particle.velocity * deltaTime;
        
        uint r = (uint)(255.0f);
        uint a = (uint)(particle.life * 255.0f);
        particle.color = a << 24 | r << 16 | r << 8 | r;
    });
    getMainLayer2D()->particleEngine.addParticleBatch(particles);
    
}

void BambooScene::update(float deltaTime)
{
    OSize frameSize = ODirector::director()->getVirtualSize();
    particles->addParticle(vec2(frameSize.width/2, frameSize.height/2), vec2(fRand(-100, 100), fRand(-100, 100)), 0xffffffff, 80);
    OScene::update(deltaTime);
}

void BambooScene::onResize()
{
    OSize frameSize = ODirector::director()->getVirtualSize();
    
    sky->setSize(vec2(frameSize.width, frameSize.height));
}

void BambooScene::onInput(float deltaTime)
{

#ifdef O_TARGET_DESKTOP
    if (OInputsManager::manager()->isKeyDown(GLFW_KEY_SPACE)) {
//        for (int i = 0; i < 20; i++) {
            
//        }
    }

#endif
}