#pragma once

#include <Core/Graphics/OWindow.h>

#include <Core/Graphics/Renderers/ORendererFactory.h>
#include <Core/Utils/OResourceManager.h>

#include <Core/OMacros.h>

NS_O_BEGIN

class OApplication {
protected:
    OWindow* m_window;

    uint m_Width, m_Height;
    
private:
    bool m_Running, m_Suspended = false, m_SuspendOnFocusLost = true;

    const char* m_Name;
    uint m_UpdatesPerSecond, m_FramesPerSecond;
    uint m_PreferredFramesPerSecond;
    
public:
    OApplication(const char* name, uint width, uint height);
    virtual ~OApplication();

    virtual void Init();

    void Start();
    void Suspend();
    void Resume();
    void Stop();

    virtual void Tick();
    virtual void Update(float deltaTime);
    virtual void Refresh();
    virtual void Render(float interpolation);
    
    const uint GetPreferredFPS() const { return m_PreferredFramesPerSecond; }
    const uint GetFPS() const { return m_FramesPerSecond; }
    const uint GetUPS() const { return m_UpdatesPerSecond; }
    
    inline void setPreferredFPS(uint fps){m_PreferredFramesPerSecond = fps;}
    inline void setFPS(uint fps){m_FramesPerSecond = fps;}
    inline void setUPS(uint ups){m_UpdatesPerSecond = ups;}
    
    inline bool isSupended() { return m_Suspended; }
    inline void setShouldSuspendWhenFocusIsLost(bool v) { m_SuspendOnFocusLost = v; }
private:
    void Run();
};

NS_O_END