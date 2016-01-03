//
//  OLayer3D.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/13/15.
//
//

#pragma once

#include <Core/OMacros.h>

NS_O_BEGIN
class OLayer3D {
    
    
public:
    OLayer3D();
    virtual ~OLayer3D();
    
    virtual void create();
    virtual void updateResoltion();
    virtual void update(float deltaTime);
    virtual void render(float interpolation);
};
NS_O_END