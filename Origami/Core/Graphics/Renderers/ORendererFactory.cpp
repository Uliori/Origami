//
//  ORendererFactory.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/16/15.
//
//

#include "ORendererFactory.h"

NS_O_BEGIN


OSimple2DShader* ORendererFactory::OShader_Simple2D;
ORendererSpriteBatch* ORendererFactory::ORenderer_SpriteBatch;

std::vector<ORenderer2D*> ORendererFactory::userRenderers;


void ORendererFactory::createRenderers()
{
    //Important : for any Shader/Renderer class you create, make sure that OpenGL initialization are implemented in shader->Init and renderer->Init methods


    //Create Shaders
    if (OShader_Simple2D == nullptr) OShader_Simple2D = new OSimple2DShader();

    //Create Renderers
    if (ORenderer_SpriteBatch == nullptr) ORenderer_SpriteBatch = new ORendererSpriteBatch();


    initRenderers();
}

void ORendererFactory::initRenderers()
{
    OShader_Simple2D->init();

    ORenderer_SpriteBatch->init();

    for (ORenderer2D* renderer : userRenderers)
    {
        renderer->init();
    }
}

void ORendererFactory::addRenderer(ORenderer2D* renderer)
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
    userRenderers.clear();
}

NS_O_END
