#include <Core/Graphics/OWindow.h>

NS_O_BEGIN

    bool OWindow::PlatformInit()
    {
        //get screen fbo
        GLint DFBO;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &DFBO);
        ODirector::director()->m_screen_fbo = (GLuint) DFBO;
        //
        
        OGLUtils::printGLInfo();
        return true;
    }
    
    void OWindow::PlatformUpdate()
    {

    }
    
    void OWindow::PlatformClean()
    {
        
    }
    
    bool OWindow::iscloseRequested() {
        return false;
    }
    
    void OWindow::PlatformVsync(bool vsync)
    {
        
    }

NS_O_END