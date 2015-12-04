#include <Core/App/OApplication.h>

namespace Origami {

    OApplication::~OApplication()
    {
        SAFE_DELETE(m_window);
        SAFE_DELETE(m_Timer);
        
        ORendererFactory::deleteRenderers();
    }
    
    void OApplication::Run()
    {

    }
    
}