//
//  ORendererFactory.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/16/15.
//
//

#pragma once

#include <vector>

//shaders
#include <Core/Graphics/Shaders/OSimple2DShader.h>

//Renderers
#include <Core/Graphics/Renderers/ORenderer2D.h>
#include <Core/Graphics/Renderers/ORendererSpriteBatch.h>

#include <Core/OMacros.h>

NS_O_BEGIN

class ORendererFactory
{
public:
    static void createRenderers();
    static void initRenderers();
    static void deleteRenderers();
    static void addRenderer(ORenderer2D* renderer);
    
    //Shaders
    static OSimple2DShader* OShader_Simple2D;

    //user Renderers
    static std::vector<ORenderer2D*> userRenderers;

    //Origami Renderers
    static ORendererSpriteBatch* ORenderer_SpriteBatch; //2D
};

NS_O_END
