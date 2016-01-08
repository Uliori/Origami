#pragma once

#include <Core/Graphics/Layers/OLayer2D.h>
#include <Core/Graphics/Layers/OLayer3D.h>


#include <Core/OMacros.h>

NS_O_BEGIN

class OScene{

private:
    OLayer3D *m_MainLayer3D;
    OLayer2D *m_MainLayer2D;
    OLayer2D *m_GUIView;
    
public:
    
    OScene();
    virtual ~OScene();

    inline OLayer3D* getMainLayer3D(){return m_MainLayer3D;}
    inline OLayer2D* getMainLayer2D(){return m_MainLayer2D;}
    inline OLayer2D* getGUIView(){return m_GUIView;}
    
    virtual void addSprite(OSprite *sprite);
    
    virtual void create();
    virtual void update(float deltaTime);
    virtual void render(float interpolation);

    virtual void onResize() {}
    virtual void onInput(float deltaTime) {}
};

NS_O_END
