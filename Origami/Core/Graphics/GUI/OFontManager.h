#pragma once

#include <vector>

#include "OFont.h"

#include <Core/OMacros.h>

NS_O_BEGIN

class OFontManager
{
private:
    static std::vector<OFont*> m_Fonts;
public:
    static void Add(OFont* font);
    static OFont* Get();
    static OFont* Get(const std::string& name);
    static OFont* Get(const std::string& name, unsigned int size);
    static void Clean();
private:
    OFontManager() { }
};

NS_O_END