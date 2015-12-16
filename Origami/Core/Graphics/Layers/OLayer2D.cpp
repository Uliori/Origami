//
//  OLayer2D.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/13/15.
//
//

#include "OLayer2D.h"


#include <Core/Graphics/Renderers/ORendererFactory.h>
#include <Core/Graphics/Scenes/OScenesManager.h>

namespace Origami {
        
    OLayer2D::OLayer2D() :  m_CurrentRenderer(ORendererFactory::ORenderer_SpriteBatch), sortType(GlyphSortType::NONE)
        {
            init();
        }
        
        OLayer2D::OLayer2D(ORenderer2D *renderer) : m_CurrentRenderer(renderer), sortType(GlyphSortType::NONE)
        {
            init();
        }
        
        void OLayer2D::init()
        {
            m_Camera = new OCamera2D(OScenesManager::Manager()->getWidth() /* OScenesManager::Manager()->getScale()*/,
                                     OScenesManager::Manager()->getHeight() /* OScenesManager::Manager()->getScale()*/);
        }
        
        OLayer2D::~OLayer2D()
        {
            SAFE_DELETE(m_Camera);
            
            for (OSprite *renderable : m_Renderables)
            {
                SAFE_DELETE(renderable);
            }
            
            //ORenderer2D is deleted in ORendererFactory ;)
        }
    
        void OLayer2D::create()
        {
            
        }
        
        void OLayer2D::update(float deltaTime)
        {
            m_Camera->update(deltaTime);
            
        }
        
        void OLayer2D::render(float interpolation)
        {
            
            if (m_CurrentRenderer) {
                m_CurrentRenderer->Begin(sortType);
                
                for (const OSprite* renderable : m_Renderables)
                    if(m_Camera->isBoxInView(renderable->GetPosition(), renderable->GetSize())){
                        renderable->Submit(m_CurrentRenderer);
                    }
                
                m_CurrentRenderer->End();
                m_CurrentRenderer->Flush(this);
            }
        
        }
}