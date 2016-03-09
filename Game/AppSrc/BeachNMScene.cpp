//
//  BeachNMScene.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 12/30/15.
//
//

#include "BeachNMScene.hpp"

BeachNMScene::BeachNMScene() : OScene()
{

}

void BeachNMScene::onCreate()
{
    
    OTexture *waveTexture   = OResourceManager::textureCache()->loadTexture("wave2.png", true, GL_REPEAT, GL_CLAMP_TO_EDGE);
    OTexture *boatTexture   = OResourceManager::textureCache()->loadTexture("boat.png");
    OTexture *mountsTexture = OResourceManager::textureCache()->loadTexture("mountains.png", true, GL_REPEAT, GL_CLAMP_TO_EDGE);

    const OSize& frameSize = ODirector::director()->getVirtualSize();
    
    float p = addPercent(frameSize.width, 50);

    //sky
    sky = new OSprite(0, 0, frameSize.width, frameSize.height, "diffuse.jpg", 0);
    sky->setColor(maths::vec4(8.0/255, 46.0/255, 59.0/255, 1.0f));

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
    sun =  new OSprite(frameSize.width * 0.65f, frameSize.height * 0.75f, 160.0, 160.0, "moon.png", 1);

    addSprite(sky);
    addSprite(mountains1);
    addSprite(wave1);
    addSprite(wave2);
    addSprite(wave3);
    addSprite(sun);
    addSprite(boat);

    particles = new OParticleBatch2D();

    particles->init(40, .9f , "star.png", .5f,
                    [](OParticleBatch2D* batch, float deltaTime){
                        const OSize& frameSize = ODirector::director()->getVirtualSize();
                        vec2 posi = vec2(fRand(0, frameSize.width), fRand(0, frameSize.height));
                        batch->addParticle(posi, vec2(), OColorRGBA8(), 15.0f);
                    },
                    [](OParticle2D& particle, float deltaTime){
                        
                        particle.position += particle.velocity * deltaTime;
                        particle.color.setAlpha(sin(MATH_PI * particle.life));
                    });
    getMainLayer2D()->particleEngine->addParticleBatch(particles);

    OResourceManager::textureCache()->releaseTexture("wave2.png");
    OResourceManager::textureCache()->releaseTexture("boat.png");
    OResourceManager::textureCache()->releaseTexture("mountains.png");


}

void BeachNMScene::onClear()
{
    
}

void BeachNMScene::onUpdate(float deltaTime)
{
      const OSize& frameSize = ODirector::director()->getVirtualSize();

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

}

void BeachNMScene::onResize()
{
    OTexture *waveTexture = wave1->getTexture();
    OTexture *mountsTexture = mountains1->getTexture();

    const OSize& frameSize = ODirector::director()->getVirtualSize();
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

    //sun
    sun->setPosition(vec2(frameSize.width * 0.65f, frameSize.height * 0.75f));

}

BeachNMScene::~BeachNMScene ()
{

}
