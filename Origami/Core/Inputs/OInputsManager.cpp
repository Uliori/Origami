//
//  OInputsManager.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/25/15.
//
//

#include "OInputsManager.h"

NS_O_BEGIN

//Singleton
OInputsManager OInputsManager::m_Instance;
OInputsManager* OInputsManager::manager()
{
    return &m_Instance;
}

OInputsManager::OInputsManager(){

}

OInputsManager::~OInputsManager()
{

}

void OInputsManager::update(){
    for (auto it : m_KeyMap)
    {
        m_PreviouskeyMap[it.first] = it.second;
    }
}

void OInputsManager::pressKey(unsigned int keyID)
{
    m_KeyMap[keyID] = true;
}

void OInputsManager::releaseKey(unsigned int keyID)
{
    m_KeyMap[keyID] = false;
}

bool OInputsManager::isKeyPressed(unsigned int keyID)
{
    if (isKeyDown(keyID) && !wasKeyDown(keyID)) {
        return true;
    }
    return false;
}

bool OInputsManager::isKeyDown(unsigned int keyID)
{
    auto it = m_KeyMap.find(keyID);
    if (it != m_KeyMap.end()) {
        return it->second;
    }
    return false;
}

bool OInputsManager::wasKeyDown(unsigned int keyID)
{
    auto it = m_PreviouskeyMap.find(keyID);
    if (it != m_PreviouskeyMap.end()) {
        return it->second;
    }
    return false;
}

NS_O_END
