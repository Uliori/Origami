#include <Core/App/OApplication.h>

namespace Origami {
    
    
    
    OApplication::OApplication(const char* name, uint width, uint height, uint scale)
    : m_Name(name), m_Width(width), m_Height(height), m_Scale(scale), m_PreferredFramesPerSecond(30)
    {

    }
        
    void OApplication::Init()
    {
        
        m_Timer = new OTimer();
        m_window = new OWindow(m_Name, m_Width, m_Height, m_Scale);
        
        ORendererFactory::initRenderers();
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
    
    void OApplication::Render()
    {
        m_window->clear();
        m_window->render();
        m_window->swapBuffers();
    }
    
    
}