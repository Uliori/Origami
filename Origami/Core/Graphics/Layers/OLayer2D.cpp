//
//  OLayer2D.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/13/15.
//
//

#include "OLayer2D.hpp"


#include <Core/Graphics/Renderers/ORendererFactory.hpp>
#include <Core/ODirector.hpp>

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
    const OSize& frameSize = ODirector::director()->getVirtualSize();
    m_Camera->setProjection(frameSize.width, frameSize.height);
}

void OLayer2D::create()
{
  const OSize& frameSize = ODirector::director()->getVirtualSize();
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
            if(renderable->shouldBeRendered(m_Camera) && !renderable->hidden){
                renderable->submit(m_CurrentRenderer);
            }

        //Send particles
        particleEngine->draw(m_CurrentRenderer);

        m_CurrentRenderer->end();
        m_CurrentRenderer->flush(getCamera());
    }

}
NS_O_END
