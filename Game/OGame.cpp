//
//  OGame.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/9/15.
//
//

#include "OGame.hpp"
#include <Core/Graphics/Scenes/OScenesManager.h>
#include <Core/Inputs/OInputsManager.h>

#include <sstream>

OGame::OGame(const char* name, uint width, uint height, uint scale):OApplication(name, width, height, scale)
{
    OLog("App Width  : " << width);
    OLog("App Height : " << height);
    OLog("App Scale  : " << scale);
    
    
}

void OGame::Init()
{
    OApplication::Init();
    
    sc1 = new scene1();
    OScenesManager::Manager()->addScene("1", sc1);
    
    
    glClearColor(0, 0, 0, 1);
    

}

void OGame::Tick()
{
//    std::ostringstream stream;
//    stream << GetFPS();
//
//   sc1->fps->setText(stream.str());
}

void OGame::Render()
{
    
    OApplication::Render();
}

void OGame::Update()
{
    OApplication::Update();
    
#ifdef O_TARGET_DESKTOP
    OLayer2D* sc1_mainLayer = sc1->getMainLayer2D();
    if (OInputsManager::Manager()->isKeyDown(GLFW_KEY_W)) {
        sc1_mainLayer->getCamera()->setPosition(sc1_mainLayer->getCamera()->getPosition() + maths::vec2(0.0f, sc1->CAM_SPEED));
    }
    
    if (OInputsManager::Manager()->isKeyDown(GLFW_KEY_S)) {
        sc1_mainLayer->getCamera()->setPosition(sc1_mainLayer->getCamera()->getPosition() + maths::vec2(0.0f, -sc1->CAM_SPEED));
    }
    
    
    if (OInputsManager::Manager()->isKeyDown(GLFW_KEY_A)) {
        sc1_mainLayer->getCamera()->setPosition(sc1_mainLayer->getCamera()->getPosition() + maths::vec2(-sc1->CAM_SPEED, 0.0f));
    }
    
    if (OInputsManager::Manager()->isKeyDown(GLFW_KEY_D)) {
        sc1_mainLayer->getCamera()->setPosition(sc1_mainLayer->getCamera()->getPosition() + maths::vec2(sc1->CAM_SPEED, 0.0f));
    }
    
//    if (inputs::OInputsManager::Manager()->isKeyDown(GLFW_KEY_Q)) {
//        sc1_mainLayer->getCamera()->setScale(sc1_mainLayer->getCamera()->getScale() - sc1->CAM_ZOOM);
//    }
//    
//    if (inputs::OInputsManager::Manager()->isKeyDown(GLFW_KEY_E)) {
//        sc1_mainLayer->getCamera()->setScale(sc1_mainLayer->getCamera()->getScale() + sc1->CAM_ZOOM);
//    }
#endif
    
  
}