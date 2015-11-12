//
//  OLayer3D.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/13/15.
//
//

#pragma once

namespace Origami {
        class OLayer3D {
            
            
        public:
            OLayer3D();
            virtual ~OLayer3D();
            
            virtual void create();
            virtual void update();
            virtual void render();
        };
}