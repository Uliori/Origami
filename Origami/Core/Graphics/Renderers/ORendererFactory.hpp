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
#include <Core/Graphics/Shaders/OTextShader.hpp>
#include <Core/Graphics/Shaders/O2DColorShader.hpp>
#include <Core/Graphics/Shaders/O2DTextureShader.hpp>

//Renderers
#include <Core/Graphics/Renderers/ORenderer2D.hpp>
#include <Core/Graphics/Renderers/ORendererSpriteBatch.hpp>
#include <Core/Graphics/Renderers/ORendererPrimitives.hpp>

#include <Core/OMacros.hpp>

NS_O_BEGIN

class ORendererFactory
{
public:
    static void createRenderers();
    static void initRenderers();
    static void deleteRenderers();
    static void addRenderer(ORenderer2D* renderer, bool init = false);
    
    //Shaders
    static O2DColorShader* OShader_Color2D;
    static O2DTextureShader* OShader_Texture2D;
    static OTextShader* OShader_Text;
    //user Renderers
    static std::vector<ORenderer2D*> userRenderers;

    //Origami Renderers
    static ORendererSpriteBatch* ORenderer_SpriteBatch; //2D
    static ORendererPrimitives* ORenderer_Primitives;
};

NS_O_END
