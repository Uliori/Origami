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
    sc3 = new BambooScene();

    ODirector::director()->addScene("1", sc1);
    ODirector::director()->addScene("2", sc2);
    ODirector::director()->addScene("3", sc3, true);
}

void OGame::tick()
{
    OLog("FPS : " << getFPS() << ",UPS : " << getUPS());
//    std::ostringstream stream;
//    stream << GetFPS();
//
//   sc1->fps->setText(stream.str());
}

void OGame::update(float deltaTime)
{
#ifdef O_TARGET_DESKTOP
    if (OInputsManager::manager()->isKeyPressed(GLFW_KEY_Q)) {
        ODirector::director()->loadScene("1");
    }
    if (OInputsManager::manager()->isKeyPressed(GLFW_KEY_W)) {
        ODirector::director()->loadScene("2");
    }
    if (OInputsManager::manager()->isKeyPressed(GLFW_KEY_E)) {
        ODirector::director()->loadScene("3");
    }
#endif

    OApplication::update(deltaTime);
}
