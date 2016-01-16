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
#include "BambooScene.hpp"

#include <Core/OMacros.h>
USING_NS_O

class OGame : public OApplication
{
    BeachScene *sc1;
    CloudsScene *sc2;
    BambooScene *sc3;

public:
    OGame(const char* name, uint width, uint height);

    void init() override;
    void tick() override;

    void update(float deltaTime) override;

};
