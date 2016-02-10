/****************************************************************************
 BeachNMScene.hpp
 
 Created by El Mehdi KHALLOUKI on 1/16/16.
 Copyright (c) 2016 __MyCompanyName__.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#include <Core/Origami.hpp>

USING_NS_O

#define WAVE_SPEED 20

class BeachNMScene : public OScene {
    
private:
    
    OSprite *sky;
    OSprite *sun;
    OSprite *boat;
    OSprite *wave1;
    OSprite *wave2;
    OSprite *wave3;
    OSprite *mountains1;
    
    OParticleBatch2D *particles;
    
    const float waterSpeed = .04f;
    
    
public:
    
    BeachNMScene();
    virtual ~BeachNMScene();
    
    void onCreate() override;
    void onClear() override;
    
    void onUpdate(float deltaTime) override;
    void onResize() override;
    
};

