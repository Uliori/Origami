//
//  OGame.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/9/15.
//
//

#pragma once

#include <Core/Utils/OGLUtils.h>
#include <Core/App/OApplication.h>

#include <Core/Graphics/Scenes/OScene.h>

#include <Core/Graphics/GUI/OFontManager.h>
#include <Core/Graphics/GUI/OFont.h>
#include <Core/Graphics/GUI/OLabel.h>

using namespace Origami;

#include <string>

class scene1 : public OScene {
    
    
public:
    OLabel *fps;
    
    const float CAM_SPEED = 2.0f;
    const float CAM_ZOOM = 0.01f;
    
    scene1()
    {
        for (uint i = 0; i < OScenesManager::Manager()->getWidth(); i += 50) {
            for (uint j = 0; j < OScenesManager::Manager()->getHeight(); j += 50) {
                addSprite(new OSprite((float)i, (float)j, 50, 50, "sprite.png"));
            }
        }
        

    }
    ~scene1 ()
    {

    }
};


class OGame : public OApplication
{
    scene1 *sc1;
public:
    OGame(const char* name, uint width, uint height, uint scale = 1);
    
    void Init() override;
    void Tick() override;
    
    void Update() override;
    void Render() override;
    
};



//        SAFE_DELETE(fnt);
