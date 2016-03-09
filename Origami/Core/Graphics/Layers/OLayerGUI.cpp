/****************************************************************************
 OLayerGUI.cpp
 
 Created by El Mehdi KHALLOUKI on 3/7/16.
 Copyright (c) 2016 __MyCompanyName__.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#include "OLayerGUI.hpp"

#include <Core/ODirector.hpp>
#include <Core/Graphics/GUI/OWidget.hpp>
#include <Core/Graphics/2D/OCamera2D.hpp>
#include <Core/Graphics/Renderers/ORendererFactory.hpp>


NS_O_BEGIN

OLayerGUI::OLayerGUI() :  m_CurrentRenderer(ORendererFactory::ORenderer_SpriteBatch)
{
    
}

OLayerGUI::~OLayerGUI()
{
    
}


void OLayerGUI::updateResolution()
{
    const OSize& frameSize = ODirector::director()->getVirtualSize();
    m_Camera->setProjection(frameSize.width, frameSize.height);
}

void OLayerGUI::create()
{
    const OSize& frameSize = ODirector::director()->getVirtualSize();
    m_Camera = new OCamera2D(frameSize.width, frameSize.height);
}

void OLayerGUI::clear()
{
    SAFE_DELETE(m_Camera);
    
    for (OWidget *renderable : m_Renderables)
    {
        SAFE_DELETE(renderable);
    }
    m_Renderables.clear();
}

void OLayerGUI::update(float deltaTime)
{
    if(m_Camera) m_Camera->update(deltaTime);
    for (OWidget *renderable : m_Renderables)
    {
        renderable->update();
    }
}

void OLayerGUI::render(float interpolation)
{
    if (m_CurrentRenderer) {
        m_CurrentRenderer->begin();
        
        //Send sprites
        for (OWidget* renderable : m_Renderables)
            renderable->submit(m_CurrentRenderer);
        
        m_CurrentRenderer->end();
        m_CurrentRenderer->flush(getCamera());
    }
    
}
NS_O_END