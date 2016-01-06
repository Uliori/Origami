//
//  OGame.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/9/15.
//
//

#include "OGame.hpp"
#include <Core/ODirector.h>

//#include <sstream>

OGame::OGame(const char* name, uint width, uint height) : OApplication(name, width, height)
{
    OLog("App Width  : " << width);
    OLog("App Height : " << height);
}
 
void OGame::Init()
{
    OApplication::Init();
    ODirector::director()->setFilesSuffixOrder();
    ODirector::director()->setDesignResolutionSize(480, 800, ResolutionPolicy::FIXED);
    
    
    sc1 = new BeachScene();
    ODirector::director()->addScene("1", sc1);
}

void OGame::Tick()
{
//    OLog("FPS : " << GetFPS() << ",UPS : " << GetUPS());
//    std::ostringstream stream;
//    stream << GetFPS();
//
//   sc1->fps->setText(stream.str());
}

void OGame::Render(float interpolation)
{
    OApplication::Render(interpolation);
}

void OGame::Update(float deltaTime)
{
    OApplication::Update(deltaTime);  
}