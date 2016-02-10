//
//  BeachScene.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 12/30/15.
//
//

#ifndef BeachScene_hpp
#define BeachScene_hpp

#include <Core/Origami.hpp>

USING_NS_O

#define WAVE_SPEED 20
#define CLOUDS_COUNT 9

class BeachScene : public OScene {
    
private:
    
    OSprite *sky;
    OSprite *sun;
    OSprite *boat;
    OSprite *wave1;
    OSprite *wave2;
    OSprite *wave3;
    OSprite *mountains1;
    
    std::vector<OSprite*> clouds;
    
    const float waterSpeed = .04f;
    
    
public:
    
    BeachScene();
    virtual ~BeachScene();
    
    void onCreate() override;
    void onClear() override;
    
    void onUpdate(float deltaTime) override;
    void onResize() override;
    
};

#endif /* BeachScene_hpp */
