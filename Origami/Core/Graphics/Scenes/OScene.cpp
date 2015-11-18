
#include "OScene.h"
#include <Core/Utils/OGLUtils.h>


namespace Origami {
    OScene::OScene()
    {
        m_MainLayer3D = new OLayer3D();
        m_MainLayer2D = new OLayer2D();
        m_GUIView = new OLayer2D();
    }

    OScene::~OScene()
    {
        SAFE_DELETE(m_GUIView)
        SAFE_DELETE(m_MainLayer2D)
        SAFE_DELETE(m_MainLayer3D)
        OLog("Scene Deleted.");
    }

    void OScene::create()
    {
        m_MainLayer3D->create();
        m_MainLayer2D->create();
        m_GUIView->create();
        OLog("Scene created.");
    }

    void OScene::update(float deltaTime)
    {
        m_MainLayer3D->update(deltaTime);
        m_MainLayer2D->update(deltaTime);
        m_GUIView->update(deltaTime);
    }

    void OScene::render()
    {
        m_MainLayer3D->render();
        m_MainLayer2D->render();
        m_GUIView->render();
    }
    
    void OScene::addSprite(OSprite *sprite)
    {
        m_MainLayer2D->addsprite(sprite);
    }

}