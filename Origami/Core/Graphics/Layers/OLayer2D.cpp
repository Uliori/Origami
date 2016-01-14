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

OLayer2D::OLayer2D(ORenderer2D *renderer) : m_CurrentRenderer(renderer)
{

}

void OLayer2D::init()
{
    OSize frameSize = ODirector::director()->getVirtualSize();
    m_Camera = new OCamera2D(frameSize.width, frameSize.height);
}

void OLayer2D::updateResolution()
{
    OSize frameSize = ODirector::director()->getVirtualSize();
    m_Camera->setProjection(frameSize.width, frameSize.height);
}

OLayer2D::~OLayer2D()
{

}

void OLayer2D::create()
{
    init();
}

void OLayer2D::clear()
{
  SAFE_DELETE(m_Camera);

  for (OSprite *renderable : m_Renderables)
  {
      SAFE_DELETE(renderable);
  }
    m_Renderables.clear();

  //ORenderer2D is deleted in ORendererFactory ;)
}

void OLayer2D::update(float deltaTime)
{
    if(m_Camera) m_Camera->update(deltaTime);

}

void OLayer2D::render(float interpolation)
{

    if (m_CurrentRenderer) {
        m_CurrentRenderer->begin();
        //Send particles

        //Send sprites
        for (const OSprite* renderable : m_Renderables)
            if(m_Camera->isBoxInView(renderable->getPosition(), renderable->getSize())){
                renderable->submit(m_CurrentRenderer);
            }

        m_CurrentRenderer->end();
        m_CurrentRenderer->flush(this);
    }

}
NS_O_END
