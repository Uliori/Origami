//
//  OSimple2DShader.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/20/15.
//
//

#pragma once

#include "OShader.h"

#include <Core/OMacros.h>

NS_O_BEGIN

class OSimple2DShader : public OShader
{
    
public:
    OSimple2DShader();
    
    void init() override;
    
private:
    void bindLocations() override;
    
};
    
NS_O_END
