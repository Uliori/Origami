#include <Core/App/OApplication.h>

NS_O_BEGIN

OApplication::OApplication(const char* name, uint width, uint height)
: m_Name(name), m_Width(width), m_Height(height), m_PreferredFramesPerSecond(30)
{

}
    
void OApplication::Init()
{
    m_window = new OWindow(m_Name, m_Width, m_Height, this);
    
    ORendererFactory::createRenderers();
}

void OApplication::Start()
{
    Init();
    m_Running = true;
    m_Suspended = false;
    Run();
}

void OApplication::Suspend()
{
    if (m_SuspendOnFocusLost) {
        ODirector::director()->pause();
        m_Suspended = true;
        OLog("Application suspended.");
    }
}

void OApplication::Resume()
{
    if (m_SuspendOnFocusLost) {
        ODirector::director()->getTimer()->reset();
        m_Suspended = false;
        OLog("Application resumed.");
    }
}

void OApplication::Stop()
{
    m_Running = false;
}

void OApplication::Tick()
{
    
}

void OApplication::Update(float deltaTime)
{
    if (!m_Suspended) {
        ODirector::director()->update(deltaTime);
    }
}

void OApplication::Refresh()
{
    m_window->refreshInput();
}

void OApplication::Render(float interpolation)
{
    m_window->clear();
    ODirector::director()->render(interpolation);
    m_window->swapBuffers();
}
    
    
NS_O_END