#include <Core/App/OApplication.hpp>

NS_O_BEGIN

OApplication::OApplication(const char* name, uint width, uint height)
:ORef(), m_Name(name), m_Width(width), m_Height(height), m_PreferredFramesPerSecond(30)
{

}

void OApplication::init()
{
    m_Window = new OWindow(m_Name, m_Width, m_Height, this);

    ORendererFactory::createRenderers();
}

void OApplication::start()
{
    init();
    m_Running = true;
    m_Suspended = false;
    run();
}

void OApplication::suspend()
{
    if (m_SuspendOnFocusLost) {
        ODirector::director()->pause();
        m_Suspended = true;
        OLog("Application suspended.");
    }
}

void OApplication::resume()
{
    if (m_SuspendOnFocusLost) {
        ODirector::director()->getTimer()->reset();
        m_Suspended = false;
        OLog("Application resumed.");
    }
}

void OApplication::stop()
{
    m_Running = false;
}

void OApplication::tick()
{

}

void OApplication::update(float deltaTime)
{
    if (!m_Suspended) {
        ODirector::director()->update(deltaTime);
    }
}

void OApplication::refresh()
{
    m_Window->refreshInput();
}

void OApplication::render(float interpolation)
{
    m_Window->clear();
    ODirector::director()->render(interpolation);
    m_Window->swapBuffers();
}


NS_O_END
