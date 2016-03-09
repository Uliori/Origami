
#include "OScene.hpp"
#include <Core/Utils/OGLUtils.hpp>
#include <Core/ODirector.hpp>

NS_O_BEGIN
OScene::OScene()
{
    m_MainLayer3D = new OLayer3D();
    m_MainLayer2D = new OLayer2D();
    m_GUIView = new OLayerGUI();

#ifdef O_MODE_DEBUG
    m_debugLayer = new OLayerGUI();
#endif
}

OScene::~OScene()
{
    clear();

#ifdef O_MODE_DEBUG
    SAFE_DELETE(m_debugLayer)
#endif
    
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
    
#ifdef O_MODE_DEBUG
    m_debugLayer->create();
    fpsLabel = new OLabel(" ");
    fpsLabel->sizetoFit();
    fpsLabel->setTextColor(OColorRGBA8(1, 1, 0));
    fpsLabel->setTextAlignment(OTEXT_ALIGN_LEFT);
    fpsLabel->setPosition(P_BOTTOM_LEFT(ODirector::director()->getVirtualSize(), fpsLabel->getSize()));
    m_debugLayer->addSubview(fpsLabel);
#endif
    
    OLog("Scene created.");
    
    onCreate();

    m_Created = true;
}

void OScene::clear()
{
    if (m_Created) {
        onClear();
        
        m_MainLayer3D->clear();
        m_MainLayer2D->clear();
        m_GUIView->clear();
        
#ifdef O_MODE_DEBUG
        m_debugLayer->clear();
#endif
        
        OLog("Scene cleared.");

        m_Created = false;
    }
}

void OScene::update(float deltaTime)
{
    if (m_Created) {
        onUpdate(deltaTime);
        
        m_MainLayer3D->update(deltaTime);
        m_MainLayer2D->update(deltaTime);
        m_GUIView->update(deltaTime);
        
#ifdef O_MODE_DEBUG
        m_debugLayer->update(deltaTime);
#endif
    }
}

void OScene::render(float interpolation)
{
    if (m_Created) {
        m_MainLayer3D->render(interpolation);
        m_MainLayer2D->render(interpolation);
        m_GUIView->render(interpolation);
        
#ifdef O_MODE_DEBUG
        if (ODirector::director()->isFPSShown()) {
            m_debugLayer->render(interpolation);
        }
#endif
    }
}

void OScene::addSprite(OSprite *sprite)
{
    m_MainLayer2D->addSprite(sprite);
}

NS_O_END
