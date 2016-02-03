//
//  OGame.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/9/15.
//
//

#pragma once

#include <Core/Origami.h>

USING_NS_O

class OGame : public OApplication
{
public:
    OGame(const char* name, uint width, uint height);

    void init() override;
    void tick() override;

    void update(float deltaTime) override;

};
