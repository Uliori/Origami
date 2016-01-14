#include <Core/App/OApplication.h>

NS_O_BEGIN

    OApplication::~OApplication()
    {
        SAFE_DELETE(m_Window);

        OResourceManager::cleanUp();
        ORendererFactory::deleteRenderers();
    }

    void OApplication::run()
    {

    }

NS_O_END
