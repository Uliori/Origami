#include <Core/Graphics/OWindow.h>

namespace Origami {
        bool OWindow::PlatformInit()
        {
            //get screen fbo
            GLint DFBO;
            glGetIntegerv(GL_FRAMEBUFFER_BINDING, &DFBO);
            OScenesManager::Manager()->m_screen_fbo = (GLuint) DFBO;
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

}