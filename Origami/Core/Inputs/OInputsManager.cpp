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
OInputsManager OInputsManager::m_instance;
OInputsManager* OInputsManager::Manager()
{
    return &m_instance;
}


OInputsManager::OInputsManager(){
    
}

OInputsManager::~OInputsManager()
{
    
}

void OInputsManager::update(){
    for (auto it : m_keyMap)
    {
        m_previouskeyMap[it.first] = it.second;
    }
}

void OInputsManager::pressKey(unsigned int keyID)
{
    m_keyMap[keyID] = true;
}

void OInputsManager::releaseKey(unsigned int keyID)
{
    m_keyMap[keyID] = false;
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
    auto it = m_keyMap.find(keyID);
    if (it != m_keyMap.end()) {
        return it->second;
    }
    return false;
}

bool OInputsManager::wasKeyDown(unsigned int keyID)
{
    auto it = m_previouskeyMap.find(keyID);
    if (it != m_previouskeyMap.end()) {
        return it->second;
    }
    return false;
}

NS_O_END