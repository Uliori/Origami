#pragma once

#include <Core/Graphics/Layers/OLayer2D.hpp>
#include <Core/Graphics/Layers/OLayer3D.hpp>

#include <Core/Inputs/OInputsManager.hpp>

#include <Core/OMacros.hpp>

NS_O_BEGIN

class OScene{

private:
    OLayer3D* m_MainLayer3D = nullptr;
    OLayer2D* m_MainLayer2D = nullptr;
    OLayer2D* m_GUIView     = nullptr;

    bool m_Created = false;
    bool m_Paused  = false;

public:

    OScene();
    virtual ~OScene();

    inline OLayer3D* getMainLayer3D(){return m_MainLayer3D;}
    inline OLayer2D* getMainLayer2D(){return m_MainLayer2D;}
    inline OLayer2D* getGUIView(){return m_GUIView;}

    /*  addSprite : will add a sprite to the MainLayer2D
     *  Sprites added to the MainLayer2D will be automatically deleted
     *  by the engine, you don;t have to delete them in the onClear method.
     */
    virtual void addSprite(OSprite* sprite);

    /*  create, clear, update : these methods are used by the engine
     *  don't override them ! use onCreate, onClear, OnUpdate.
     *  update and render methods are called by the engine depending on the preferred
     *  frames per second.
     */
    void create();
    void clear();
    void update(float deltaTime);
    void render(float interpolation);
    
    /*  onCreate : will be called when the scene is loaded, you should initialize 
     *  your objects here.
     */
    virtual void onCreate() {}
    /*  onClear  : will be called when the scene is cleared, you should clear and delete
     *  your objects here.
     */
    virtual void onClear() {}
    
    /*  onUpdate are called by the engine depending on the preferred
     *  frames per second.
     */
    virtual void onUpdate(float deltaTime) {}
    
    /*  onResize : will be called when the window size is changed, or when the orientation
     *  change, you should override that method if your game support multiple orientations.
     */
    virtual void onResize() {}

    virtual void onInput(OInputsManager *inputsManager, float deltaTime) {}

    inline bool isCreated() { return m_Created; }

    inline void pause() { m_Paused = true; }
    inline void resume() { m_Paused = false; }
    inline bool isPaused() { return m_Paused; }

};

NS_O_END
