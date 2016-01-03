#include <Core/App/OApplication.h>

NS_O_BEGIN

OApplication::OApplication(const char* name, uint width, uint height)
: m_Name(name), m_Width(width), m_Height(height), m_PreferredFramesPerSecond(30)
{

}
    
void OApplication::Init()
{
    
    m_Timer = new OTimer();
    m_window = new OWindow(m_Name, m_Width, m_Height);
    
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
    m_Suspended = true;
}

void OApplication::Resume()
{
    m_Suspended = false;
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
    m_window->update(deltaTime);
}

void OApplication::Refresh()
{
    m_window->refreshInput();
}

void OApplication::Render(float interpolation)
{
    m_window->clear();
    m_window->render(interpolation);
    m_window->swapBuffers();
}
    
    
NS_O_END