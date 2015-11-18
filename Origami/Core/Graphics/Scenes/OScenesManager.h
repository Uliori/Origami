#pragma once

#include "OScene.h"

#include <map>
#include <string>

namespace Origami {

    class OScenesManager {
    private:
        //singleton
        static OScenesManager* m_instance;
    public:
        //singleton
        static OScenesManager* Manager();
        static void DeleteManager();
        
        
    private:

        OScene *m_CurrentScene;
        std::map<std::string, OScene*> m_Scenes;
        
        std::string m_CurrentSceneID;
        int m_Width, m_Height, m_Scale;
    public:
        uint m_screen_fbo;
        
        
    public:
        
        OScenesManager();
        virtual ~OScenesManager();
        
        
        void loadGame();
        
        void updateCurrentScene(float deltaTime);
        void renderCurrentScene();
        
        void updateScene(OScene *scene, float deltaTime);
        void renderScene(OScene *scene);
        
        void addScene(const std::string& scene_name, OScene *scene, bool setCurrent = false);
        void deleteScene(const std::string& scene_name);
        
        void loadScene(const std::string& scene_name);
        
        
        inline uint getWidth() const { return m_Width; }
        inline uint getHeight() const { return m_Height; }
        inline uint getScale() const { return m_Scale; }
        
        inline void setDimensions(uint width, uint height, uint scale) { m_Width = width; m_Height = height; m_Scale = scale; }
    };
        
}