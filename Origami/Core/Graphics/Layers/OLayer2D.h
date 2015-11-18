//
//  OLayer2D.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/13/15.
//
//

#pragma once

#include <Core/Graphics/2D/OCamera2D.h>

#include <Core/Graphics/Renderers/ORenderer2D.h>
#include <Core/Graphics/2D/OSprite.h>

#include <vector>

namespace Origami {
    
        class OLayer2D {
        private:
            
            std::vector<OSprite *> m_Renderables;
            
            ORenderer2D *m_CurrentRenderer;
            
            OCamera2D *m_Camera;
        public:
            OLayer2D();
            OLayer2D(ORenderer2D *renderer);
            
            
            virtual ~OLayer2D();
            
            inline void addsprite(OSprite * sprite) {m_Renderables.push_back(sprite);}
            
            inline void setRenderer(ORenderer2D * renderer){m_CurrentRenderer = renderer;}
            
            inline OCamera2D * getCamera() const { return m_Camera; }
            
            virtual void create();
            virtual void update(float deltaTime);
            virtual void render();
            
        private:
            void init();
        };
}