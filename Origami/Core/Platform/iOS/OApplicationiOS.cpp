#include <Core/App/OApplication.h>

NS_O_BEGIN

OApplication::~OApplication()
{
    SAFE_DELETE(m_window);
    SAFE_DELETE(m_Timer);
    
    OResourceManager::cleanUp();
    ORendererFactory::deleteRenderers();
}

void OApplication::Run()
{

}

NS_O_END