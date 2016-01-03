#include <Core/Graphics/OWindow.h>

NS_O_BEGIN
        bool OWindow::PlatformInit()
        {
            ODirector::director()->m_screen_fbo = 0;
            
            OGLUtils::printGLInfo();
            return true;
        }
        
        void OWindow::PlatformUpdate()
        {
            //EGL swap buffers
        }
        
        void OWindow::PlatformClean()
        {
            
        }
        
        bool OWindow::iscloseRequested() {
            return false;
        }
        
        void OWindow::PlatformVsync(bool vsync)
        {
            //EGL swap interval
        }

NS_O_END