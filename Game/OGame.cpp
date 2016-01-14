//
//  OGame.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/9/15.
//
//

#include "OGame.hpp"
#include <Core/ODirector.h>
#include <Core/Inputs/OInputsManager.h>

//#include <sstream>

OGame::OGame(const char* name, uint width, uint height) : OApplication(name, width, height)
{
    OLog("Application Width  : " << width);
    OLog("Application Height : " << height);
}

void OGame::init()
{
    OApplication::init();
    ODirector::director()->setFilesSuffixOrder();
    ODirector::director()->setDesignResolutionSize(480, 800, ResolutionPolicy::FIXED);

    sc1 = new BeachScene();
    sc2 = new CloudsScene();

    ODirector::director()->addScene("1", sc1);
    ODirector::director()->addScene("2", sc2);
}

void OGame::tick()
{
//    OLog("FPS : " << GetFPS() << ",UPS : " << GetUPS());
//    std::ostringstream stream;
//    stream << GetFPS();
//
//   sc1->fps->setText(stream.str());
}

void OGame::update(float deltaTime)
{
#ifdef O_TARGET_DESKTOP
    if (OInputsManager::manager()->isKeyPressed(GLFW_KEY_1)) {
        ODirector::director()->loadScene("1");
    }
    if (OInputsManager::manager()->isKeyPressed(GLFW_KEY_2)) {
        ODirector::director()->loadScene("2");
    }
#endif

    OApplication::update(deltaTime);
}
