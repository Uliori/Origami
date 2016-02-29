//
//  O2DTextureShader.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/20/15.
//
//

#pragma once

#include "OShader.hpp"

#include <Core/OMacros.hpp>

NS_O_BEGIN

class O2DTextureShader : public OShader
{
    
public:
    O2DTextureShader();
    
    void init() override;
    void prepare(OCamera2D *camera) override;
private:
    void bindLocations() override;
    
};
    
NS_O_END
