//
//  ORendererFactory.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/16/15.
//
//

#include "ORendererFactory.h"

namespace Origami {
    
    
OSimple2DShader * ORendererFactory::OShader_Simple2D;
ORendererSpriteBatch * ORendererFactory::ORenderer_SpriteBatch;
    
    
    
std::vector<ORenderer2D *> ORendererFactory::userRenderers;
    
    void ORendererFactory::initRenderers()
    {
        //Init Shaders
        OShader_Simple2D = new OSimple2DShader();
        
        //Init Renderers
        ORenderer_SpriteBatch = new ORendererSpriteBatch();
    }
    
    void ORendererFactory::addRenderer(ORenderer2D * renderer)
    {
        userRenderers.push_back(renderer);
    }
    
    void ORendererFactory::deleteRenderers()
    {
        //delete shaders
        SAFE_DELETE(OShader_Simple2D);
        
        
        //delete renderers
        SAFE_DELETE(ORenderer_SpriteBatch);
        for (ORenderer2D *renderer : userRenderers)
        {
            SAFE_DELETE(renderer);
        }
    }

}