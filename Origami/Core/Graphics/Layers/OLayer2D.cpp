//
//  OLayer2D.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/13/15.
//
//

#include "OLayer2D.h"


#include <Core/Graphics/Renderers/ORendererFactory.h>
#include <Core/ODirector.h>

NS_O_BEGIN
        
OLayer2D::OLayer2D() :  m_CurrentRenderer(ORendererFactory::ORenderer_SpriteBatch)
{
    init();
}

OLayer2D::OLayer2D(ORenderer2D *renderer) : m_CurrentRenderer(renderer)
{
    init();
}

void OLayer2D::init()
{
    OSize frameSize = ODirector::director()->getVirtualSize();
    m_Camera = new OCamera2D(frameSize.width, frameSize.height);
}

void OLayer2D::updateResoltion()
{
    OSize frameSize = ODirector::director()->getVirtualSize();
    m_Camera->setProjection(frameSize.width, frameSize.height);
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
        m_CurrentRenderer->Begin();
        
        for (const OSprite* renderable : m_Renderables)
            if(m_Camera->isBoxInView(renderable->GetPosition(), renderable->GetSize())){
                renderable->Submit(m_CurrentRenderer);
            }
        
        m_CurrentRenderer->End();
        m_CurrentRenderer->Flush(this);
    }

}
NS_O_END