//
//  BeachScene.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 12/30/15.
//
//

#ifndef BeachScene_hpp
#define BeachScene_hpp


#include <Core/ODirector.h>
#include <Core/Graphics/Scenes/OScene.h>

#include <Core/Utils/OTime.h>
#include <Core/Maths/OMaths.h>

#include <Core/OMacros.h>
USING_NS_O

#define WAVE_SPEED 20
#define CLOUDS_COUNT 9

class BeachScene : public OScene {
    
private:
    OTimer *timer;
    
    OSprite *sun;
    OSprite *boat;
    OSprite *wave1;
    OSprite *wave2;
    OSprite *wave3;
    OSprite *mountains1;
    
    std::vector<OSprite*> clouds;
    
    const float CAM_SPEED = 150.0f;
    const float CAM_ZOOM = 0.01f;
    
    const float waterSpeed = .04f;
    
    
public:
    
    BeachScene();
    virtual ~BeachScene();
    
    void update(float deltaTime) override;
    void onResize() override;
    
};

#endif /* BeachScene_hpp */
