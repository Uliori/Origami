//
//  OInputsManager.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/25/15.
//
//

#pragma once

#include <unordered_map>

#include <Core/OMacros.hpp>
#include <Core/Maths/OMaths.hpp>

NS_O_BEGIN

struct TouchPoint
{
public:
    unsigned int hashId;
    maths::vec2 position;
    maths::vec2 lastPosition;
    bool down;
    
    enum TouchEvent
    {
        TOUCH_PRESS,
        TOUCH_MOVE,
        TOUCH_RELEASE
    };
    
    TouchPoint()
    {
        hashId = 0;
        position = maths::vec2();
        lastPosition = maths::vec2();
        down = false;
    }
};

#define TOUCH_POINTS_MAX (10)

class OInputsManager {
private:
    //singleton
    static OInputsManager m_Instance;
public:
    //singleton
    static OInputsManager* manager();

public:
    OInputsManager();
    virtual ~OInputsManager();

    //Screen touch
    TouchPoint touchPoints[TOUCH_POINTS_MAX];
    //Mouse position
    TouchPoint mousePoint;
    
    void update();

    void pressKey(unsigned int keyID);
    void releaseKey(unsigned int keyID);

    //returns true if a key was held down
    bool isKeyDown(unsigned int keyID);

    //returns true if a key was just pressed
    bool isKeyPressed(unsigned int keyID);

    //Mouse position setter / getter
    void setMousePosition(const maths::vec2& position) { mousePoint.position = position; }
    const maths::vec2& getMousePosition() { return mousePoint.position; }
    
private:
    std::unordered_map<unsigned int, bool> m_KeyMap;
    std::unordered_map<unsigned int, bool> m_PreviouskeyMap;
    
    bool wasKeyDown(unsigned int keyID);
};

NS_O_END
