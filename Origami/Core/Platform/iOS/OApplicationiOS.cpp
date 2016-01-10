#include <Core/App/OApplication.h>

NS_O_BEGIN

OApplication::~OApplication()
{
    SAFE_DELETE(m_window);
    
    OResourceManager::cleanUp();
    ORendererFactory::deleteRenderers();
}

void OApplication::Run()
{

}

NS_O_END