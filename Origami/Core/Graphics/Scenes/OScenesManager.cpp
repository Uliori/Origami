


#include "OScenesManager.h"
#include <Core/Utils/OGLUtils.h>

namespace Origami {

    //Singleton
    OScenesManager* OScenesManager::m_instance = new OScenesManager();
    OScenesManager* OScenesManager::Manager()
    {
        return m_instance;
    }
    void OScenesManager::DeleteManager()
    {
        SAFE_DELETE(m_instance);
    }
         
            
    OScenesManager::OScenesManager() : m_CurrentScene(nullptr)
    {
        
    }


    OScenesManager::~OScenesManager()
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


    void OScenesManager::loadGame()
    {
        //TODO : load a game main file that will contain all scenes
        OLog("Game loading ...");
    }

    void OScenesManager::updateCurrentScene(float deltaTime)
    {
        updateScene(m_CurrentScene, deltaTime);
    }

    void OScenesManager::renderCurrentScene()
    {
        renderScene(m_CurrentScene);
    }

    void OScenesManager::updateScene(OScene *scene, float deltaTime)
    {
        if (scene) {
            m_CurrentScene->update(deltaTime);
        }
    }

    void OScenesManager::renderScene(OScene *scene)
    {
        if (scene) {
            m_CurrentScene->render();
        }
    }

    void OScenesManager::addScene(const std::string& scene_name, OScene *scene, bool setCurrent)
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

    void OScenesManager::deleteScene(const std::string& scene_name)
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

    void OScenesManager::loadScene(const std::string& scene_name)
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

    
}
