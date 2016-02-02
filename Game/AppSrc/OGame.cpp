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


    m_Clouds    = new CloudsScene();
   m_Beach     = new BeachScene();
   m_BeachNM   = new BeachNMScene();
   m_BeachA    = new BeachAScene();
   m_Particles = new ParticlesScene();
   m_Particlest= new Particles2Scene();
   m_Bamboo    = new BambooScene();

  ODirector::director()->addScene("1", m_Clouds);
   ODirector::director()->addScene("2", m_Beach);
   ODirector::director()->addScene("3", m_BeachNM);
   ODirector::director()->addScene("4", m_BeachA);
   ODirector::director()->addScene("5", m_Particles);
   ODirector::director()->addScene("6", m_Particlest);
   ODirector::director()->addScene("9", m_Bamboo);

    ODirector::director()->loadScene("1");
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
