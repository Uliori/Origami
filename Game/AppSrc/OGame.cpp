//
//  OGame.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/9/15.
//
//

#include "OGame.hpp"

//sand
#include "CloudsScene.hpp"
#include "BeachScene.hpp"
#include "BeachNMScene.hpp"
#include "BeachAScene.hpp"
#include "BambooScene.hpp"
#include "ParticlesScene.hpp"
#include "Particles2Scene.hpp"
#include "SandboxScene.hpp"

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

    ODirector::director()->addScene("1", new CloudsScene());
    ODirector::director()->addScene("2", new BeachScene());
    ODirector::director()->addScene("3", new BeachNMScene());
    ODirector::director()->addScene("4", new BeachAScene());
    ODirector::director()->addScene("5", new ParticlesScene());
    ODirector::director()->addScene("6", new Particles2Scene());
    ODirector::director()->addScene("9", new BambooScene());
    ODirector::director()->addScene("sandbox", new SandboxScene());
    
//    ODirector::director()->loadScene("1");
    ODirector::director()->loadScene("sandbox");
}

void OGame::tick()
{
//  OLog("FPS : " << getFPS() << ",UPS : " << getUPS());
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
    if (OInputsManager::manager()->isKeyPressed(GLFW_KEY_3)) {
        ODirector::director()->loadScene("3");
    }
    if (OInputsManager::manager()->isKeyPressed(GLFW_KEY_4)) {
        ODirector::director()->loadScene("4");
    }
    if (OInputsManager::manager()->isKeyPressed(GLFW_KEY_5)) {
        ODirector::director()->loadScene("5");
    }
    if (OInputsManager::manager()->isKeyPressed(GLFW_KEY_6)) {
        ODirector::director()->loadScene("6");
    }
#endif

    OApplication::update(deltaTime);
}
