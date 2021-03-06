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

BambooScene::BambooScene()
{
    
}

BambooScene::~BambooScene()
{
    
}

void BambooScene::onCreate()
{
    const OSize& frameSize = ODirector::director()->getVirtualSize();
    
    //sky
    sky = new OSprite(0, 0, frameSize.width, frameSize.height, "bsky.png", 0);
    addSprite(sky);
    
    particles = new OParticleBatch2D();
    
    particles->init(40, .9f , "cloud.png", 5,
                    [](OParticleBatch2D* batch, float deltaTime){
                        const OSize& frameSize = ODirector::director()->getVirtualSize();
                        vec2 posi = vec2(fRand(0, frameSize.width), fRand(0, frameSize.height));
                        batch->addParticle(posi, vec2(), OColorRGBA8(), 20);
                    },
                    [](OParticle2D& particle, float deltaTime){
                        particle.position += particle.velocity * deltaTime;
                        particle.color.setAlpha(particle.life);
    });
    getMainLayer2D()->particleEngine->addParticleBatch(particles);
    
}

void BambooScene::onClear()
{
    
}

void BambooScene::onResize()
{
    const OSize& frameSize = ODirector::director()->getVirtualSize();
    
    sky->setSize(vec2(frameSize.width, frameSize.height));
}
