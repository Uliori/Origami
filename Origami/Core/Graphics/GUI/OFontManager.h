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
    static void add(OFont* font);
    static OFont* get();
    static OFont* get(const std::string& name);
    static OFont* get(const std::string& name, unsigned int size);
    static void clean();
private:
    OFontManager() { }
};

NS_O_END
