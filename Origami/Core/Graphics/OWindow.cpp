#include "OWindow.h"
#include <Core/Inputs/OInputsManager.h>
namespace Origami {

		OWindow::OWindow(const char* title, uint width, uint height, uint scale)
			:m_Title(title), m_Width(width), m_Height(height), m_Scale(scale), m_Closed(false)
		{
			
			if (!init()) {
				OErrLog("Window initialization failed !");
				return;
			}
            SetVsync(true);

			refreshInput();
		}

		OWindow::~OWindow()
		{
			PlatformClean();
            OScenesManager::DeleteManager();
		}

		bool OWindow::init()
		{
			if (!PlatformInit()) {
				OErrLog("Platform initialization failed !");
				return false;
			}
            
            OScenesManager::Manager()->setDimensions(m_Width, m_Height, m_Scale);
            OScenesManager::Manager()->loadGame();
            
			return true;
		}

        void OWindow::setDimensions(uint width, uint height, uint scale) {
            
            m_Width = width;
            m_Height = height;
            m_Scale = scale;
            
            OScenesManager::Manager()->setDimensions(m_Width, m_Height, m_Scale);
        }


        bool OWindow::closed() const
        {
            return m_Closed;
        }
        
		void OWindow::SetVsync(bool enabled)
		{
			m_Vsync = enabled;
            PlatformVsync(m_Vsync);
		}

		void OWindow::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void OWindow::update(float deltaTime)
		{
            OScenesManager::Manager()->updateCurrentScene(deltaTime);
		}
        
        void OWindow::render(float interpolation)
        {
            OScenesManager::Manager()->renderCurrentScene(interpolation);
        }
        
        void OWindow::swapBuffers()
        {
            PlatformUpdate();
        }

		void OWindow::refreshInput()
		{
            OInputsManager::Manager()->update();
		}

}