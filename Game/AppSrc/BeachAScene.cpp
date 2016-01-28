/****************************************************************************
 BeachAScene.cpp
 
 Created by El Mehdi KHALLOUKI on 1/22/16.
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

//
//  BeachAScene.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 12/30/15.
//
//

#include "BeachAScene.hpp"

#include <Core/Utils/OResourceManager.h>
#include <Core/Inputs/OInputsManager.h>
#include <Core/Graphics/2D/OParticleBach2D.hpp>

bool BeachAScene::isDay = true;

BeachAScene::BeachAScene() : OScene()
{
    
}

void BeachAScene::create()
{
    OScene::create();
    
    OTexture *waveTexture   = OResourceManager::textureCache()->loadTexture("wave2.png", true, GL_REPEAT, GL_CLAMP_TO_EDGE);
    OTexture *boatTexture   = OResourceManager::textureCache()->loadTexture("boat.png");
    OTexture *cloudTexture  = OResourceManager::textureCache()->loadTexture("cloud.png");
    OTexture *sunTexture    = OResourceManager::textureCache()->loadTexture("sun.png");
    OTexture *mountsTexture = OResourceManager::textureCache()->loadTexture("mountains.png", true, GL_REPEAT, GL_CLAMP_TO_EDGE);
    
    OSize frameSize = ODirector::director()->getVirtualSize();
    float p = addPercent(frameSize.width, 50);
    
    //sky
    sky = new OSprite(0, 0, frameSize.width, frameSize.height, "diffuse.jpg", 0);
    
    //boat
    boat = new OSprite(frameSize.width * 0.75f, 45, boatTexture->getWidth(), boatTexture->getHeight(), "boat.png", 3);
    
    //mountains
    mountains1 = new OSprite(0, 10, p, mountsTexture->getHeight(), "mountains.png", 1);
    mountains1->setUV(maths::vec4(0.0f, 0.0f, p / mountsTexture->getWidth(), 1.0f));
    
    //w3
    wave3 = new OSprite(0, 30, p, waveTexture->getHeight(), "wave2.png", 5);
    wave3->setUV(maths::vec4(0.0f, 0.0f, p / waveTexture->getWidth(), 1.0f));
    
    //w2
    wave2 = new OSprite(0, 00, p, waveTexture->getHeight(), "wave2.png", 4);
    wave2->setUV(maths::vec4(0.0f, 0.0f, p / waveTexture->getWidth(), 1.0f));
    
    //w1
    wave1 = new OSprite(0, -30, p, waveTexture->getHeight(), "wave2.png", 2);
    wave1->setUV(maths::vec4(0.0f, 0.0f, p / waveTexture->getWidth(), 1.0f));//
    
    //sun
    sun =  new OSprite(frameSize.width * 0.75f, frameSize.height * 0.75f, sunTexture->getWidth(), sunTexture->getHeight(), "sun.png", 1);
    
    //moon
    moon =  new OSprite(frameSize.width * 0.65f, frameSize.height * 0.75f, 160.0, 160.0, "moon.png", 1);
    
    currentMinutes = ODirector::director()->getTimer()->getDayMinutesTime();
    if (currentMinutes >= 360 && currentMinutes <= 1080) { //jour
        isDay = true;
    }
    else //nuit
    {
        isDay = false;
    }
    
    for (int i = 0; i < CLOUDS_COUNT; i++) {
        clouds.push_back(new OSprite(maths::fRand(0, frameSize.width),
                                     maths::fRand(percent(frameSize.height, 60), percent(frameSize.height, 80)),
                                     cloudTexture->getWidth(),
                                     cloudTexture->getHeight(),
                                     "cloud.png",
                                     2));
        clouds.back()->hidden = !isDay;
        clouds.back()->tag = maths::fRand(10, 20);
        addSprite(clouds.back());
    }
    
    particles = new OParticleBatch2D();
    
    particles->init(40, .9f , "star.png", .5f,
                    [](OParticleBatch2D* batch, float deltaTime){
                        if (!BeachAScene::isDay) {
                            OSize frameSize = ODirector::director()->getVirtualSize();
                            vec2 posi = vec2(fRand(0, frameSize.width), fRand(0, frameSize.height));
                            batch->addParticle(posi, vec2(), OColorRGBA8(), 15.0f);
                        }
                    },
                    [](OParticle2D& particle, float deltaTime){
                        particle.position += particle.velocity * deltaTime;
                        particle.color.setAlpha(sin(MATH_PI * particle.life));
                    });
    getMainLayer2D()->particleEngine->addParticleBatch(particles);
    
    addSprite(sky);
    addSprite(mountains1);
    addSprite(wave1);
    addSprite(wave2);
    addSprite(wave3);
    addSprite(sun);
    addSprite(moon);
    addSprite(boat);
    
    OResourceManager::textureCache()->releaseTexture("wave2.png");
    OResourceManager::textureCache()->releaseTexture("boat.png");
    OResourceManager::textureCache()->releaseTexture("cloud.png");
    OResourceManager::textureCache()->releaseTexture("sun.png");
    OResourceManager::textureCache()->releaseTexture("mountains.png");
}

void BeachAScene::clear()
{
    clouds.clear();
    OScene::clear();
}

void BeachAScene::update(float deltaTime)
{
    OSize frameSize = ODirector::director()->getVirtualSize();
    
    currentMinutes = ODirector::director()->getTimer()->getDayMinutesTime();
    
    //debugging stuffs
//    currentMinutes += 2;
//    if (currentMinutes > 1440) {
//        currentMinutes = 0;
//    }
//    OLog(currentMinutes);
    //debugging stuffs - End
    
    if (currentMinutes >= 360 && currentMinutes <= 1080) { //jour
        isDay = true;
        sun->hidden = false;
        moon->hidden = true;
        
//      convert from 360->720->1080 to 0->Pi/2->Pi
        float v = ((float)(currentMinutes - 360) / 720.0f) * MATH_PI;

        //sun
        sun->setPosition(vec2(frameSize.width * 0.75f, (frameSize.height * 0.75f) * sin(v)));
        
        //sky color
        const maths::vec3 startColor = maths::vec3(135.0/255, 206.0/255, 235.0/255);
        const maths::vec3 endColor   = maths::vec3(8.0/255, 46.0/255, 59.0/255);
        maths::vec3 pColor = (endColor - startColor) * (1 - sin(v)) + startColor;

        sky->setColor(maths::vec4(pColor, 1.0f));
    }
    else //nuit
    {
        isDay = false;
        sun->hidden = true;
        moon->hidden = false;
        
        sky->setColor(maths::vec4(8.0/255, 46.0/255, 59.0/255, 1.0f));
        
    }
    
    float time = sin(ODirector::director()->getTimer()->getTime() / 1000.0);
    float p = percent(frameSize.width, 50);
    float st = sin(time);
    
    maths::vec2 position = wave1->getPosition();
    wave1->setPosition(maths::vec2(-p/2.0f - st * WAVE_SPEED, 30 + st * WAVE_SPEED));
    
    position = wave2->getPosition();
    wave2->setPosition(maths::vec2(-p/2.0f + st * WAVE_SPEED, st * WAVE_SPEED));
    
    position = wave3->getPosition();
    wave3->setPosition(maths::vec2(-p/2.0f - st * WAVE_SPEED,  -30 + st * WAVE_SPEED));
    
    position = boat->getPosition();
    boat->setPosition(maths::vec2(p + st * 60,  30 + sin(time * 2.5f) * WAVE_SPEED));
    
    for (OSprite *cloud : clouds)
    {
        position = cloud->getPosition();
        cloud->setPosition(maths::vec2(position.x + cloud->tag * deltaTime, position.y));
        if (cloud->getPosition().x > frameSize.width)
        {
            cloud->hidden = !isDay;
            cloud->setPosition(maths::vec2(- cloud->getSize().x, position.y));
        }
        
    }
    
    OScene::update(deltaTime);
}


void BeachAScene::onResize()
{
    OTexture *waveTexture = wave1->getTexture();
    OTexture *mountsTexture = mountains1->getTexture();
    
    OSize frameSize = ODirector::director()->getVirtualSize();
    float p = addPercent(frameSize.width, 50);
    
    sky->setSize(vec2(frameSize.width, frameSize.height));
    
    //boat
    boat->setPosition(vec2(frameSize.width * 0.75f, 45.0f));
    
    //mountains
    mountains1->setSize(vec2(p, mountsTexture->getHeight()));
    mountains1->setUV(maths::vec4(0.0f, 0.0f, p / mountsTexture->getWidth(), 1.0f));
    
    //w3
    wave3->setSize(vec2(p, waveTexture->getHeight()));
    wave3->setUV(maths::vec4(0.0f, 0.0f, p / waveTexture->getWidth(), 1.0f));
    
    //w2
    wave2->setSize(vec2(p, waveTexture->getHeight()));
    wave2->setUV(maths::vec4(0.0f, 0.0f, p / waveTexture->getWidth(), 1.0f));
    
    //w1
    wave1->setSize(vec2(p, waveTexture->getHeight()));
    wave1->setUV(maths::vec4(0.0f, 0.0f, p / waveTexture->getWidth(), 1.0f));//
    
    for (int i = 0; i < CLOUDS_COUNT; i++) {
        OSprite *cloud = clouds.at(i);
        cloud->setPosition(vec2(maths::fRand(0, frameSize.width), maths::fRand(percent(frameSize.height, 60), percent(frameSize.height, 80))));
    }
}

BeachAScene::~BeachAScene ()
{
    
}
