//
//  ORendererFactory.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/16/15.
//
//

#include "ORendererFactory.hpp"

NS_O_BEGIN

//shaders
O2DTextureShader* ORendererFactory::OShader_Texture2D = nullptr;
O2DColorShader* ORendererFactory::OShader_Color2D = nullptr;
OTextShader* ORendererFactory::OShader_Text = nullptr;

//Renderers
ORendererSpriteBatch* ORendererFactory::ORenderer_SpriteBatch = nullptr;
ORendererPrimitives* ORendererFactory::ORenderer_Primitives = nullptr;

std::vector<ORenderer2D*> ORendererFactory::userRenderers;

void ORendererFactory::createRenderers()
{
    //Important : for any Shader/Renderer class you create, make sure that OpenGL initialization are implemented in shader->init and renderer->init methods


    //Create Shaders
    if (OShader_Color2D == nullptr) OShader_Color2D = new O2DColorShader();
    if (OShader_Texture2D == nullptr) OShader_Texture2D = new O2DTextureShader();
    if (OShader_Text == nullptr) OShader_Text = new OTextShader();

    //Create Renderers
    if (ORenderer_SpriteBatch == nullptr) ORenderer_SpriteBatch = new ORendererSpriteBatch();
    if (ORenderer_Primitives == nullptr) ORenderer_Primitives = new ORendererPrimitives();

    initRenderers();
}

void ORendererFactory::initRenderers()
{
    OShader_Color2D->init();
    OShader_Texture2D->init();
    OShader_Text->init();
    
    ORenderer_SpriteBatch->init();
    ORenderer_Primitives->init();

    for (ORenderer2D* renderer : userRenderers)
    {
        renderer->init();
    }
}

void ORendererFactory::addRenderer(ORenderer2D* renderer, bool init/* = false*/)
{
    userRenderers.push_back(renderer);
    if (init)
        renderer->init();
}

void ORendererFactory::deleteRenderers()
{
    //delete shaders
    SAFE_DELETE(OShader_Color2D);
    SAFE_DELETE(OShader_Texture2D);
    SAFE_DELETE(OShader_Text);

    //delete renderers
    SAFE_DELETE(ORenderer_SpriteBatch);
    SAFE_DELETE(ORenderer_Primitives);
    
    for (ORenderer2D *renderer : userRenderers)
    {
        SAFE_DELETE(renderer);
    }
    userRenderers.clear();
}

NS_O_END
