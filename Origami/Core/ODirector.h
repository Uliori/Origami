#pragma once

#include <map>
#include <string>

#include <Core/OMacros.h>
#include <Core/Maths/OGeometry.h>
#include <Core/Graphics/Scenes/OScene.h>


NS_O_BEGIN

enum class ResolutionPolicy
{
    /** The application takes the height of the design resolution size and modifies the width of the virtual
     * frame size so that it fits the aspect ratio of the device.
     * No distortion will occur however you must make sure your application works on different
     * aspect ratios.
     */
    FIXED_HEIGHT,
    /** The application takes the width of the design resolution size and modifies the height of the virtual
     * frame size so that it fits the aspect ratio of the device.
     * No distortion will occur however you must make sure your application works on different
     * aspect ratios.
     */
    FIXED_WIDTH,
    /** The application will use FIXED_HEIGHT if the screen width is > screen height, and FIXED_WIDTH otherwise.
     ** You may use this if your game support both portrait and landscape orientations.
     */
    FIXED,
};


class ODirector {
private:
    //singleton
    static ODirector* m_instance;
public:
    //singleton
    static ODirector* director();
    static void DeleteManager();
    
    uint m_screen_fbo;
    
private:
    
    OScene *m_CurrentScene = nullptr;
    std::map<std::string, OScene*> m_Scenes;
    
    std::string m_CurrentSceneID;
    
    OSize m_FrameSize;
    OSize m_DesignResolutionSize;
    OSize m_VirtualSize;
    
    float m_ScaleX;
    float m_ScaleY;
    ResolutionPolicy m_resolutionPolicy;
    
    void updateDesignResolutionSize();

public:
    
    ODirector();
    virtual ~ODirector();
    
    
    void loadGame();
    
    void updateCurrentScene(float deltaTime);
    void renderCurrentScene(float interpolation);
    
    void updateScene(OScene *scene, float deltaTime);
    void renderScene(OScene *scene, float interpolation);
    inline OScene * getCurrentScene() {return m_CurrentScene;}
    
    void addScene(const std::string& scene_name, OScene *scene, bool setCurrent = false);
    void deleteScene(const std::string& scene_name);
    
    void loadScene(const std::string& scene_name);
    
    
    inline OSize& getFrameSize() {return m_FrameSize;}
    inline OSize& getDesignResolutionSize() {return m_DesignResolutionSize;}
    inline OSize& getVirtualSize() {return m_VirtualSize;}
    inline ResolutionPolicy &getResolutionPolicy() {return m_resolutionPolicy;}
    
    void setFrameSize(uint width, uint height) { m_FrameSize = OSize(width, height);}
    void setDesignResolutionSize(uint width, uint height, ResolutionPolicy resolutionPolicy);
};
        
NS_O_END