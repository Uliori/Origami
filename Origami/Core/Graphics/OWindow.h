#pragma once

#include <Core/ODirector.h>
#include <Core/Utils/OGLUtils.h>

#include <Core/OMacros.h>

NS_O_BEGIN

#define MAX_KEYS 512
#define MAX_BUTTONS 5

class OWindow {
private:
    const char* m_Title;

    bool m_Closed;
    bool m_Vsync;

#ifdef O_TARGET_DESKTOP
    GLFWwindow *m_Window;
#endif
    
    int m_Width, m_Height;
public:
    OWindow(const char* title, uint width, uint height);
    ~OWindow();

    
    void clear() const;
    void refreshInput();
    
    
    void update(float deltaTime);
    void render(float interpolation);
    void swapBuffers();
    
    bool iscloseRequested();
    bool closed() const;

    void setDimensions(uint width, uint height);
    inline uint getWidth() const { return m_Width; }
    inline uint getHeight() const { return m_Height; }

    void SetVsync(bool enabled);
    inline bool IsVsync() const { return m_Vsync; }
    
private:
    bool init();

    bool PlatformInit();
    void PlatformUpdate();
    void PlatformClean();
    void PlatformVsync(bool vsync);
};
NS_O_END