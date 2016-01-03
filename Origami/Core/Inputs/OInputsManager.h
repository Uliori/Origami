//
//  OInputsManager.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/25/15.
//
//

#pragma once

#include <unordered_map>

#include <Core/OMacros.h>

NS_O_BEGIN

class OInputsManager {
private:
    //singleton
    static OInputsManager m_instance;
public:
    //singleton
    static OInputsManager* Manager();
    
    
    
    
public:
    OInputsManager();
    virtual ~OInputsManager();
    
    void update();
    
    void pressKey(unsigned int keyID);
    void releaseKey(unsigned int keyID);
    
    //returns true if a key was held down
    bool isKeyDown(unsigned int keyID);
    
    //returns true if a key was just pressed
    bool isKeyPressed(unsigned int keyID);
    
    
private:
    std::unordered_map<unsigned int, bool> m_keyMap;
    std::unordered_map<unsigned int, bool> m_previouskeyMap;
    
    bool wasKeyDown(unsigned int keyID);
};
    
NS_O_END
