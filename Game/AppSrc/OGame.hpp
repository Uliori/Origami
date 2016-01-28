//
//  OGame.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/9/15.
//
//

#pragma once

#include <Core/App/OApplication.h>

#include "CloudsScene.hpp"
#include "BeachScene.hpp"
#include "BeachNMScene.hpp"
#include "BeachAScene.hpp"
#include "BambooScene.hpp"
#include "ParticlesScene.hpp"
#include "Particles2Scene.hpp"

#include <Core/OMacros.h>
USING_NS_O

class OGame : public OApplication
{
    CloudsScene*        m_Clouds;
    BeachScene*         m_Beach;
    BeachNMScene*       m_BeachNM;
    BeachAScene*        m_BeachA;
    ParticlesScene*     m_Particles;
    Particles2Scene*    m_Particlest;
    BambooScene*        m_Bamboo;

public:
    OGame(const char* name, uint width, uint height);

    void init() override;
    void tick() override;

    void update(float deltaTime) override;

};
