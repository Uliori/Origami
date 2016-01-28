#include <Core/Graphics/OWindow.h>

NS_O_BEGIN
        bool OWindow::platformInit()
        {
            ODirector::director()->screen_fbo = 0;

            OGLUtils::printGLInfo();
            return true;
        }

        void OWindow::platformUpdate()
        {
            //EGL swap buffers
        }

        void OWindow::platformClean()
        {

        }

        bool OWindow::iscloseRequested() {
            return false;
        }

        void OWindow::platformVsync(bool vsync)
        {
            //EGL swap interval
        }

NS_O_END
