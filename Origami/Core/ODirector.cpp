


#include "ODirector.h"
#include <Core/Utils/OGLUtils.h>

NS_O_BEGIN

//Singleton
ODirector* ODirector::m_instance;
ODirector* ODirector::director()
{
    if (!m_instance) {
        m_instance = new ODirector();
    }
    return m_instance;
}
void ODirector::DeleteManager()
{
    SAFE_DELETE(m_instance);
}
     
        
ODirector::ODirector() : m_CurrentScene(nullptr)
{
    
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
    
}

void ODirector::setDesignResolutionSize(uint width, uint height, ResolutionPolicy resolutionPolicy)
{
    m_DesignResolutionSize = OSize(width, height);
    m_resolutionPolicy = resolutionPolicy;
    
    updateDesignResolutionSize();
    if (m_CurrentScene) {
        m_CurrentScene->getMainLayer2D()->updateResoltion();
        m_CurrentScene->getMainLayer3D()->updateResoltion();
        m_CurrentScene->getGUIView()->updateResoltion();
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
        
        if ( m_resolutionPolicy == ResolutionPolicy::FIXED_HEIGHT
            || (m_resolutionPolicy == ResolutionPolicy::FIXED && m_FrameSize.width > m_FrameSize.height))
        {
            m_ScaleX = m_ScaleY;
            m_VirtualSize.height = m_DesignResolutionSize.height;
            m_VirtualSize.width  = ceilf(m_FrameSize.width/m_ScaleX);
        }
        
        else if ( m_resolutionPolicy == ResolutionPolicy::FIXED_WIDTH
                 || (m_resolutionPolicy == ResolutionPolicy::FIXED && m_FrameSize.height > m_FrameSize.width))
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

void ODirector::updateCurrentScene(float deltaTime)
{
    updateScene(m_CurrentScene, deltaTime);
}

void ODirector::renderCurrentScene(float interpolation)
{
    renderScene(m_CurrentScene, interpolation);
}

void ODirector::updateScene(OScene *scene, float deltaTime)
{
    if (scene) {
        m_CurrentScene->update(deltaTime);
    }
}

void ODirector::renderScene(OScene *scene, float interpolation)
{
    if (scene) {
        m_CurrentScene->render(interpolation);
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
    if (setCurrent || m_CurrentScene == nullptr) {
        loadScene(scene_name);
    }
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
        m_CurrentScene = s_scene->second;
        m_CurrentSceneID = scene_name;
        OLog("Current Scene is : " << scene_name);
        
        m_CurrentScene->create();
    }
    else
    {
        OLog("Scene \"" << scene_name << "\" not found !");
    }
}

NS_O_END
