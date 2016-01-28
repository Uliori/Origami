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

}

OLayer2D::OLayer2D(ORenderer2D* renderer) : m_CurrentRenderer(renderer)
{

}

OLayer2D::~OLayer2D()
{

}


void OLayer2D::updateResolution()
{
    OSize frameSize = ODirector::director()->getVirtualSize();
    m_Camera->setProjection(frameSize.width, frameSize.height);
}

void OLayer2D::create()
{
  OSize frameSize = ODirector::director()->getVirtualSize();
  m_Camera = new OCamera2D(frameSize.width, frameSize.height);
  particleEngine = new OParticleEngine2D();
}

void OLayer2D::clear()
{
    SAFE_DELETE(m_Camera);
    SAFE_DELETE(particleEngine);

    for (OSprite *renderable : m_Renderables)
    {
        SAFE_DELETE(renderable);
    }
    m_Renderables.clear();
}

void OLayer2D::update(float deltaTime)
{
    if(m_Camera) m_Camera->update(deltaTime);
    if(particleEngine) particleEngine->update(deltaTime);
}

void OLayer2D::render(float interpolation)
{
    if (m_CurrentRenderer) {
        m_CurrentRenderer->begin();

        //Send sprites
        for ( OSprite* renderable : m_Renderables)
            if(m_Camera->isBoxInView(renderable->getPosition(), renderable->getSize()) && !renderable->hidden){
                renderable->submit(m_CurrentRenderer);
            }

        //Send particles
        particleEngine->draw(m_CurrentRenderer);

        m_CurrentRenderer->end();
        m_CurrentRenderer->flush(this);
    }

}
NS_O_END
