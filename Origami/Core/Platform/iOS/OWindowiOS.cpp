#include <Core/Graphics/OWindow.hpp>

NS_O_BEGIN

    bool OWindow::platformInit()
    {
        //get screen fbo
        GLint DFBO;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &DFBO);
        ODirector::director()->screen_fbo = (GLuint) DFBO;
        //

        OGLUtils::printGLInfo();
        return true;
    }

    void OWindow::platformUpdate()
    {

    }

    void OWindow::platformClean()
    {

    }

    bool OWindow::iscloseRequested() {
        return false;
    }

    void OWindow::platformVsync(bool vsync)
    {

    }

NS_O_END
