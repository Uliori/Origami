#pragma once

#include <Core/ORef.hpp>

#include <Core/Graphics/OWindow.h>

#include <Core/Graphics/Renderers/ORendererFactory.h>
#include <Core/Utils/OResourceManager.h>

#include <Core/OMacros.h>

NS_O_BEGIN

class OApplication : public ORef {
protected:
    OWindow* m_Window = nullptr;

    uint m_Width, m_Height;

private:
    bool m_Running, m_Suspended = false, m_SuspendOnFocusLost = true;

    const char* m_Name;
    uint m_UpdatesPerSecond, m_FramesPerSecond;
    uint m_PreferredFramesPerSecond;

public:
    OApplication(const char* name, uint width, uint height);
    virtual ~OApplication();

    virtual void init();

    void start();
    void suspend();
    void resume();
    void stop();

    virtual void tick();
    virtual void update(float deltaTime);
    virtual void refresh();
    virtual void render(float interpolation);

    const uint getPreferredFPS() const { return m_PreferredFramesPerSecond; }
    const uint getFPS() const { return m_FramesPerSecond; }
    const uint getUPS() const { return m_UpdatesPerSecond; }

    inline void setPreferredFPS(uint fps){m_PreferredFramesPerSecond = fps;}
    inline void setFPS(uint fps){m_FramesPerSecond = fps;}
    inline void setUPS(uint ups){m_UpdatesPerSecond = ups;}

    inline bool isSupended() { return m_Suspended; }
    inline void setShouldSuspendWhenFocusIsLost(bool v) { m_SuspendOnFocusLost = v; }
private:
    void run();
};

NS_O_END
