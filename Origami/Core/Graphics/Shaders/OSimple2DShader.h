//
//  OSimple2DShader.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/20/15.
//
//

#pragma once

#include "OShader.h"

namespace Origami {

    class OSimple2DShader : public OShader
    {
        
    public:
        OSimple2DShader();
        
    private:
        void BindLocations() override;
    };
    
}
