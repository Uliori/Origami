//
//  OGame.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/9/15.
//
//

#pragma once

#include <Core/App/OApplication.h>

#include "BeachScene.hpp"
#include "CloudsScene.hpp"

#include <Core/OMacros.h>
USING_NS_O

class OGame : public OApplication
{
    BeachScene *sc1;
    CloudsScene *sc2;
    
public:
    OGame(const char* name, uint width, uint height);
    
    void Init() override;
    void Tick() override;
    
    void Update(float deltaTime) override;
    void Render(float interpolation) override;
    
};

