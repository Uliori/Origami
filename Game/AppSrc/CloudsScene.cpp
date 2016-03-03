/****************************************************************************
 CloudsScene.cpp

 Created by El Mehdi KHALLOUKI on 1/9/16.
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

#include "CloudsScene.hpp"

CloudsScene::CloudsScene() : OScene()
{

}

void CloudsScene::onCreate()
{
    OTexture *cloudTexture  = OResourceManager::textureCache()->loadTexture("cloud.png");

    OSize frameSize = ODirector::director()->getVirtualSize();

    //sky
    sky = new OSprite(0, 0, frameSize.width, frameSize.height, "diffuse.jpg", 0);
    sky->setColor(maths::vec4(135.0/255, 206.0/255, 235.0/255, 1.0f));
    addSprite(sky);

    //clouds
    for (int i = 0; i < CLOUDS_COUNT; i++) {
        m_Clouds.push_back(new OSprite(maths::fRand(0, frameSize.width),
                                     maths::fRand(percent(frameSize.height, 40), percent(frameSize.height, 80)),
                                     cloudTexture->getWidth(),
                                     cloudTexture->getHeight(),
                                     "cloud.png",
                                     2));

        m_Clouds.back()->tag = maths::fRand(10, 20);
        addSprite(m_Clouds.back());
    }


    OResourceManager::textureCache()->releaseTexture("cloud.png");
    
    
}

void CloudsScene::onClear()
{
    m_Clouds.clear();
}

void CloudsScene::onUpdate(float deltaTime)
{
    OSize frameSize = ODirector::director()->getVirtualSize();
    maths::vec2 position;

    for (OSprite *cloud : m_Clouds)
    {
        position = cloud->getPosition();
        cloud->setPosition(maths::vec2(position.x + cloud->tag * deltaTime, position.y));
        if (cloud->getPosition().x > frameSize.width)
        {
            cloud->setPosition(maths::vec2(- cloud->getSize().x, position.y));
        }

    }
}

void CloudsScene::onResize()
{

    OSize frameSize = ODirector::director()->getVirtualSize();
    
    
    sky->setSize(vec2(frameSize.width, frameSize.height));

    for (int i = 0; i < CLOUDS_COUNT; i++) {
        OSprite *cloud = m_Clouds.at(i);
        cloud->setPosition(vec2(maths::fRand(0, frameSize.width), maths::fRand(percent(frameSize.height, 60), percent(frameSize.height, 80))));
    }
}

CloudsScene::~CloudsScene()
{

}
