//
//  BeachScene.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 12/30/15.
//
//

#include "BeachScene.hpp"

#include <Core/Utils/OResourceManager.h>
#include <Core/Inputs/OInputsManager.h>

BeachScene::BeachScene() : OScene()
{

}

void BeachScene::create()
{
    std::string wave1img  = "wave2.png";
    std::string boatimg   = "boat.png";
    std::string cloudimg  = "cloud.png";
    std::string sunimg    = "sun.png";
    std::string mountsimg = "mountains.png";
    
    OTexture waveTexture   = OResourceManager::loadTexture(wave1img, true, GL_REPEAT, GL_CLAMP_TO_EDGE);
    OTexture boatTexture   = OResourceManager::loadTexture(boatimg);
    OTexture cloudTexture  = OResourceManager::loadTexture(cloudimg);
    OTexture sunTexture    = OResourceManager::loadTexture(sunimg);
    OTexture mountsTexture = OResourceManager::loadTexture(mountsimg, true, GL_REPEAT, GL_CLAMP_TO_EDGE);
    
    OSize frameSize = ODirector::director()->getVirtualSize();
    
    float p = addPercent(frameSize.width, 50);
    
    //boat
    boat = new OSprite(frameSize.width * 0.75f, 45, boatTexture.getWidth(), boatTexture.getHeight(), boatimg, 3);
    
    //mountains
    mountains1 = new OSprite(0, 10, p, mountsTexture.getHeight(), mountsimg, 1);
    mountains1->SetUV(maths::vec4(0.0f, 0.0f, p / mountsTexture.getWidth(), 1.0f));
    
    //w3
    wave3 = new OSprite(0, 30, p, waveTexture.getHeight(), wave1img, 5);
    wave3->SetUV(maths::vec4(0.0f, 0.0f, p / waveTexture.getWidth(), 1.0f));
    
    //w2
    wave2 = new OSprite(0, 00, p, waveTexture.getHeight(), wave1img, 4);
    wave2->SetUV(maths::vec4(0.0f, 0.0f, p / waveTexture.getWidth(), 1.0f));
    
    //w1
    wave1 = new OSprite(0, -30, p, waveTexture.getHeight(), wave1img, 2);
    wave1->SetUV(maths::vec4(0.0f, 0.0f, p / waveTexture.getWidth(), 1.0f));//
    
    //sun
    sun =  new OSprite(frameSize.width * 0.75f, frameSize.height * 0.75f, sunTexture.getWidth(), sunTexture.getHeight(), sunimg, 1);
    
    
    addSprite(mountains1);
    addSprite(wave1);
    addSprite(wave2);
    addSprite(wave3);
    addSprite(sun);
    addSprite(boat);
    
    
    for (int i = 0; i < CLOUDS_COUNT; i++) {
        clouds.push_back(new OSprite(maths::fRand(0, frameSize.width),
                                     maths::fRand(percent(frameSize.height, 60), percent(frameSize.height, 80)),
                                     cloudTexture.getWidth(),
                                     cloudTexture.getHeight(),
                                     cloudimg,
                                     2));
        
        clouds.back()->tag = maths::fRand(10, 20);
        addSprite(clouds.back());
    }
    
    OScene::create();
}

void BeachScene::update(float deltaTime)
{
    OSize frameSize = ODirector::director()->getVirtualSize();
    
    float time = sin(ODirector::director()->getTimer()->getTime() / 1000.0);
    float p = percent(frameSize.width, 50);
    //        float ct = cos(time);
    float st = sin(time);
    
    
    maths::vec2 position = wave1->GetPosition();
    wave1->setPosition(maths::vec2(-p/2.0f - st * WAVE_SPEED, 30 + st * WAVE_SPEED));
    
    position = wave2->GetPosition();
    wave2->setPosition(maths::vec2(-p/2.0f + st * WAVE_SPEED, st * WAVE_SPEED));
    
    position = wave3->GetPosition();
    wave3->setPosition(maths::vec2(-p/2.0f - st * WAVE_SPEED,  -30 + st * WAVE_SPEED));
    
    
    position = boat->GetPosition();
    boat->setPosition(maths::vec2(p + st * 60,  30 + sin(time * 2.5f) * WAVE_SPEED));
    
    for (OSprite *cloud : clouds)
    {
        position = cloud->GetPosition();
        cloud->setPosition(maths::vec2(position.x + cloud->tag * deltaTime, position.y));
        if (cloud->GetPosition().x > frameSize.width)
        {
            cloud->setPosition(maths::vec2(- cloud->GetSize().x, position.y));
        }
        
    }
    glClearColor(135.0/255, 206.0/255, 235.0/255, 1.0f);

    OScene::update(deltaTime);
}

void BeachScene::onInput(float deltaTime)
{
#ifdef O_TARGET_DESKTOP
    OLayer2D* sc1_mainLayer = getMainLayer2D();
    if (OInputsManager::Manager()->isKeyDown(GLFW_KEY_W)) {
        sc1_mainLayer->getCamera()->setPosition(sc1_mainLayer->getCamera()->getPosition() + (maths::vec2(0.0f, CAM_SPEED) * deltaTime));
    }
    
    if (OInputsManager::Manager()->isKeyDown(GLFW_KEY_S)) {
        sc1_mainLayer->getCamera()->setPosition(sc1_mainLayer->getCamera()->getPosition() + (maths::vec2(0.0f, -CAM_SPEED) * deltaTime));
    }
    
    
    if (OInputsManager::Manager()->isKeyDown(GLFW_KEY_A)) {
        sc1_mainLayer->getCamera()->setPosition(sc1_mainLayer->getCamera()->getPosition() + (maths::vec2(-CAM_SPEED, 0.0f) * deltaTime));
    }
    
    if (OInputsManager::Manager()->isKeyDown(GLFW_KEY_D)) {
        sc1_mainLayer->getCamera()->setPosition(sc1_mainLayer->getCamera()->getPosition() + (maths::vec2(CAM_SPEED, 0.0f) * deltaTime));
    }
    
    //    OLog(deltaTime);
    //    if (inputs::OInputsManager::Manager()->isKeyDown(GLFW_KEY_Q)) {
    //        sc1_mainLayer->getCamera()->setScale(sc1_mainLayer->getCamera()->getScale() - sc1->CAM_ZOOM);
    //    }
    //
    //    if (inputs::OInputsManager::Manager()->isKeyDown(GLFW_KEY_E)) {
    //        sc1_mainLayer->getCamera()->setScale(sc1_mainLayer->getCamera()->getScale() + sc1->CAM_ZOOM);
    //    }
    
#endif
}

void BeachScene::onResize()
{
    std::string wave1img = "wave2.png";
    std::string boatimg = "boat.png";
    std::string cloudimg = "cloud.png";
    std::string sunimg = "sun.png";
    std::string mountsimg = "mountains.png";
    
    OTexture waveTexture = OResourceManager::loadTexture(wave1img);
    OTexture sunTexture = OResourceManager::loadTexture(sunimg);
    OTexture mountsTexture = OResourceManager::loadTexture(mountsimg);
    
    OSize frameSize = ODirector::director()->getVirtualSize();
    
    float p = addPercent(frameSize.width, 50);
    
    //boat
    boat->setPosition(vec2(frameSize.width * 0.75f, 45.0f));
    
    
    //mountains
    mountains1->setSize(vec2(p, mountsTexture.getHeight()));
    mountains1->SetUV(maths::vec4(0.0f, 0.0f, p / mountsTexture.getWidth(), 1.0f));
    
    //w3
    wave3->setSize(vec2(p, waveTexture.getHeight()));
    wave3->SetUV(maths::vec4(0.0f, 0.0f, p / waveTexture.getWidth(), 1.0f));
    
    //w2
    wave2->setSize(vec2(p, waveTexture.getHeight()));
    wave2->SetUV(maths::vec4(0.0f, 0.0f, p / waveTexture.getWidth(), 1.0f));
    
    //w1
    wave1->setSize(vec2(p, waveTexture.getHeight()));
    wave1->SetUV(maths::vec4(0.0f, 0.0f, p / waveTexture.getWidth(), 1.0f));//
    
    //sun
    sun->setSize(vec2(sunTexture.getWidth(), sunTexture.getHeight()));
    sun->setPosition(vec2(frameSize.width * 0.75f, frameSize.height * 0.75f));
    
    for (int i = 0; i < CLOUDS_COUNT; i++) {
        OSprite *cloud = clouds.at(i);
        cloud->setPosition(vec2(maths::fRand(0, frameSize.width), maths::fRand(percent(frameSize.height, 60), percent(frameSize.height, 80))));
    }
}

BeachScene::~BeachScene ()
{

}
