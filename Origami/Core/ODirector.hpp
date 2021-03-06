#pragma once

#include <map>
#include <string>
#include <vector>

#include <Core/OMacros.hpp>
#include <Core/Utils/OTime.hpp>
#include <Core/Maths/OGeometry.hpp>
#include <Core/Graphics/Scenes/OScene.hpp>
#include <Core/Inputs/OInputsManager.hpp>
#include <Core/Graphics/GUI/OFontManager.hpp>


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

struct FileSuffix {
    std::string suffix;
    int scale;
    FileSuffix(std::string dsuffix, int dscale)
    {
        suffix = dsuffix;
        scale = dscale;
    }
};

class ODirector {
private:
    //singleton
    static ODirector* m_Instance;
public:
    //singleton
    static ODirector* director();
    static void deleteManager();

    // that uint will store the screen fbo
    uint screen_fbo;

    //Search path list, depending on the screen resolution
    std::vector<FileSuffix> fileExtensions;
private:
    //Scenes data
    OScene* m_CurrentScene = nullptr;
    std::map<std::string, OScene*> m_Scenes;
    std::string m_CurrentSceneID;

    //General Timer
    OTimer* m_Timer;

    //Screen resolution, desired resolution, and calculated resolution depending on the screen ratio
    OSize m_FrameSize;
    OSize m_DesignResolutionSize;
    OSize m_VirtualSize;

    void updateInput();
    
    float m_ScaleX;
    float m_ScaleY;
    ResolutionPolicy m_ResolutionPolicy;

    void updateDesignResolutionSize();
    
    bool shouldShowFPS = false;
public:

    ODirector();
    virtual ~ODirector();

    //that method will load the game file configuration in the future
    virtual void loadGame();
    
    virtual void update(float deltaTime);
    virtual void render(float interpolation);

    OTimer* getTimer() const { return m_Timer;}

    void updateCurrentScene(float deltaTime);
    void renderCurrentScene(float interpolation);

    void updateScene(OScene* scene, float deltaTime);
    void renderScene(OScene* scene, float interpolation);
    
    inline OScene* getCurrentScene() {return m_CurrentScene;}
    inline std::string getCurrentSceneID(){ return m_CurrentSceneID; }

    void reloadScene(OScene *scene);
    void reloadCurrentScene();

    void addScene(const std::string& scene_name, OScene *scene, bool setCurrent = false);
    void deleteScene(const std::string& scene_name);

    // load the scene and call its create method
    void loadScene(const std::string& scene_name);

    void init();
    void pause();
    void resume();

    const OSize& getFrameSize() const {return m_FrameSize;}
    const OSize& getDesignResolutionSize() const {return m_DesignResolutionSize;}
    
    /**
     * @desc return the screen calculated size based on the DesignResolutionSize 
     *       and the ResolutionPolicy.
     * @return OSize - the screen rect.
     */
    const OSize& getVirtualSize() const {return m_VirtualSize;}
    const float getScaleX() const { return m_ScaleX; }
    const float getScaleY() const { return m_ScaleY; }
    inline ResolutionPolicy &getResolutionPolicy() {return m_ResolutionPolicy;}

    void setFrameSize(uint width, uint height) { m_FrameSize = OSize(width, height);}
    void setDesignResolutionSize(uint width, uint height, ResolutionPolicy resolutionPolicy);

    void setFilesSuffixOrder();

    void showFPS(bool fps) { shouldShowFPS = fps; }
    bool isFPSShown() { return shouldShowFPS; }
    
    void setFPSValue(const std::string& fpsv);
    
    //
    void handleTouch(int hashID, TouchPoint::TouchEvent event, const maths::vec2& position, const maths::vec2& oldPosition);
private:
    std::map<int, OInputEvents*> m_TouchMap;
};

NS_O_END
