


#include "ODirector.hpp"
#include <Core/Utils/OGLUtils.hpp>
#include <Core/Utils/ResourcesUtils.hpp>

NS_O_BEGIN

//Singleton
ODirector* ODirector::m_Instance;
ODirector* ODirector::director()
{
    if (!m_Instance) {
        m_Instance = new ODirector();
    }
    return m_Instance;
}

void ODirector::deleteManager()
{
    SAFE_DELETE(m_Instance);
}

ODirector::ODirector() : m_CurrentScene(nullptr)
{
    
}

void ODirector::init()
{
    m_Timer = new OTimer();
}

ODirector::~ODirector()
{
    //delete all scenes
    for(auto iterator : m_Scenes)
    {
        std::string scene_name = iterator.first;
        if (m_CurrentSceneID == scene_name) {
            m_CurrentScene = nullptr;
        }
        SAFE_DELETE(iterator.second)
    }
    m_Scenes.clear();
    //

    SAFE_DELETE(m_Timer);
    
    OFontManager::clean();
}

void ODirector::setFilesSuffixOrder()
{
    fileExtensions.clear();

    OSize screenSize = getFrameSize();
    float minR = MIN(screenSize.width, screenSize.height);
    if (minR > 768) { //iPad retina like
        fileExtensions.push_back(FileSuffix("-x4", 4));
        fileExtensions.push_back(FileSuffix("-x2", 2));
        fileExtensions.push_back(FileSuffix("-x1", 1));
        fileExtensions.push_back(FileSuffix("", 1));
    }
    else if (minR > 320) { //iPhone Retina & iPad like
        fileExtensions.push_back(FileSuffix("-x2", 2));
        fileExtensions.push_back(FileSuffix("-x1", 1));
        fileExtensions.push_back(FileSuffix("", 1));
    }
    else { //iPhone like
        fileExtensions.push_back(FileSuffix("-x1", 1));
        fileExtensions.push_back(FileSuffix("", 1));
    }
}

void ODirector::setDesignResolutionSize(uint width, uint height, ResolutionPolicy resolutionPolicy)
{
    m_DesignResolutionSize = OSize(width, height);
    m_ResolutionPolicy = resolutionPolicy;

    OSize OvirtualS = getVirtualSize();
    updateDesignResolutionSize();
    OSize NvirtualS = getVirtualSize();

    if (OvirtualS.width == NvirtualS.width && OvirtualS.height == NvirtualS.height)
        return;

    if (m_CurrentScene) {
        m_CurrentScene->getMainLayer2D()->updateResolution();
        m_CurrentScene->getMainLayer3D()->updateResolution();
        m_CurrentScene->getGUIView()->updateResolution();
#ifdef O_MODE_DEBUG
          m_CurrentScene->getDebugGUIView()->updateResolution();
#endif
      
        m_CurrentScene->onResize();
    }
}

void ODirector::updateDesignResolutionSize()
{
    if (m_FrameSize.width > 0 && m_FrameSize.height > 0
        && m_DesignResolutionSize.width > 0 && m_DesignResolutionSize.height > 0)
    {
        m_ScaleX = (float)m_FrameSize.width / m_DesignResolutionSize.width;
        m_ScaleY = (float)m_FrameSize.height / m_DesignResolutionSize.height;

        if ( m_ResolutionPolicy == ResolutionPolicy::FIXED_HEIGHT
            || (m_ResolutionPolicy == ResolutionPolicy::FIXED && m_FrameSize.width > m_FrameSize.height))
        {
            m_ScaleX = m_ScaleY;
            m_VirtualSize.height = m_DesignResolutionSize.height;
            m_VirtualSize.width  = ceilf(m_FrameSize.width/m_ScaleX);
        }

        else if ( m_ResolutionPolicy == ResolutionPolicy::FIXED_WIDTH
                 || (m_ResolutionPolicy == ResolutionPolicy::FIXED && m_FrameSize.height > m_FrameSize.width))
        {
            m_ScaleY = m_ScaleX;
            m_VirtualSize.width  = m_DesignResolutionSize.width;
            m_VirtualSize.height = ceilf(m_FrameSize.height/m_ScaleY);
        }

        // calculate the rect of viewport
//        float viewPortW = m_VirtualSize.width * m_ScaleX;
//        float viewPortH = m_VirtualSize.height * m_ScaleY;
//        OLog("vsw : " << m_VirtualSize.width << ", vsh : " << m_VirtualSize.height);
//        OLog("vpw : " << viewPortW << ", vph : " << viewPortH);
    }
}

void ODirector::loadGame()
{
    //TODO : load a game main file that will contain all scenes
    OLog("Game loading ...");
}

void ODirector::update(float deltaTime)
{
#ifdef O_TARGET_DESKTOP
    updateInput();
#endif
    updateCurrentScene(deltaTime);
}

void ODirector::render(float interpolation)
{
    renderCurrentScene(interpolation);
}

void ODirector::updateCurrentScene(float deltaTime)
{
    updateScene(m_CurrentScene, deltaTime);
}

void ODirector::renderCurrentScene(float interpolation)
{
    renderScene(m_CurrentScene, interpolation);
}

void ODirector::reloadScene(OScene *scene)
{
    if (scene && scene->isCreated()) {
        scene->clear();
        scene->create();
    }
}

void ODirector::setFPSValue(const std::string& fpsv)
{
    if (m_CurrentScene && m_CurrentScene->isCreated()) {
        m_CurrentScene->setFPSValue(fpsv);
    }
}

void ODirector::reloadCurrentScene()
{
    reloadScene(m_CurrentScene);
}

void ODirector::updateScene(OScene *scene, float deltaTime)
{
    if (scene && scene->isCreated()) {
        scene->onInput(OInputsManager::manager(), deltaTime);
        scene->update(deltaTime);
    }
}

void ODirector::renderScene(OScene *scene, float interpolation)
{
    if (scene && scene->isCreated()) {
        scene->render(interpolation);
    }
}

void ODirector::pause()
{
    if (m_CurrentScene) {
        m_CurrentScene->pause();
    }
}

void ODirector::resume()
{
    if (m_CurrentScene) {
        m_CurrentScene->resume();
    }
}

void ODirector::addScene(const std::string& scene_name, OScene *scene, bool setCurrent)
{
    auto s_scene = m_Scenes.find(scene_name);
    if(s_scene != m_Scenes.end())
    {
        OLog("Scene \"" << scene_name << "\" already exists !");
        return;
    }

    m_Scenes.insert(std::make_pair(scene_name, scene));
//     if (setCurrent || m_CurrentScene == nullptr) {
//         loadScene(scene_name);
//     }
}

void ODirector::deleteScene(const std::string& scene_name)
{
    auto s_scene = m_Scenes.find(scene_name);
    if(s_scene != m_Scenes.end())
    {
        if (m_CurrentSceneID == scene_name) {
            m_CurrentScene = nullptr;
        }

        SAFE_DELETE(s_scene->second)
        m_Scenes.erase(s_scene);
    }
}

void ODirector::loadScene(const std::string& scene_name)
{
    auto s_scene = m_Scenes.find(scene_name);
    if(s_scene != m_Scenes.end())
    {
        if (m_CurrentScene && m_CurrentScene->isCreated()) {
          m_CurrentScene->clear();
        }
        m_CurrentScene = s_scene->second;
        m_CurrentSceneID = scene_name;
        OLog("Current Scene is : " << scene_name);

        if (m_CurrentScene && !m_CurrentScene->isCreated()) {
            m_CurrentScene->create();
        }
    }
    else
    {
        OLog("Scene \"" << scene_name << "\" not found !");
    }
}

void ODirector::updateInput() // for desktop only
{
    auto& touches =  OInputsManager::manager()->getTouchPoints();
    const maths::vec2& position = OInputsManager::manager()->getMousePosition();
    
    for (auto& it : touches)
    {
        auto& touch = it.second;
        touch.position = position;
        if (touch.down && touch.position != touch.lastPosition) {
            handleTouch(touch.hashId, TouchPoint::TOUCH_MOVE, position, touch.lastPosition);
            touch.lastPosition = position;
        }
    }
}

void ODirector::handleTouch(int hashID, TouchPoint::TouchEvent event, const maths::vec2& position, const maths::vec2& oldPosition)
{
    const maths::vec2 screenScale = maths::vec2(ODirector::director()->getScaleX(), ODirector::director()->getScaleY());
    
    maths::vec2 StFPosi     = maths::vec2(position.x / screenScale.x, position.y / screenScale.y);
    maths::vec2 StFLastPosi = maths::vec2(oldPosition.x / screenScale.x, oldPosition.y / screenScale.y);
    
    auto it = m_TouchMap.find(hashID);
    if(it != m_TouchMap.end())
    {
        it->second->touchEvent(hashID, event, StFPosi, StFLastPosi);
        if (event == TouchPoint::TOUCH_RELEASE) {
            m_TouchMap.erase(it);
        }
    }
    else {
        bool touchOnWidget = false;
        OLayerGUI* guiLayer = m_CurrentScene->getGUIView();
        maths::vec2 FtWPosi = guiLayer->getCamera()->convertScreenToWorld(StFPosi);
        
        for (OWidget* widget : guiLayer->m_Renderables) {
            if (widget->isTouchInside(FtWPosi)) {
                touchOnWidget = true;
                m_TouchMap.insert(std::make_pair(hashID, widget));
                widget->touchEvent(hashID, event, StFPosi, StFLastPosi);
                break;
            }
        }
        if (!touchOnWidget) {
            if (m_CurrentScene && m_CurrentScene->isCreated()) {
                m_TouchMap.insert(std::make_pair(hashID, m_CurrentScene));
                m_CurrentScene->touchEvent(hashID, event, StFPosi, StFLastPosi);
            }
        }
    }
}
NS_O_END
