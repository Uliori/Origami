#include <Core/App/OApplication.h>
#include <Core/Inputs/OInputsManager.h>

namespace Origami {

    OApplication::~OApplication()
    {
        
        SAFE_DELETE(m_window);
        SAFE_DELETE(m_Timer);
        glfwTerminate();
        
        ORendererFactory::deleteRenderers();
    }

	void OApplication::Run()
	{
        double          processTime        = 0;
        double          tickCounter        = 0;
        float           updateTick         = 1.0f/m_PreferredFramesPerSecond;
        unsigned int    frames             = 0;
        unsigned int    updates            = 0;
        
        float MS_IN_SECONDS = 1000.0f;
        
        //TODO : this is not perfect, you should check it later
        m_Timer->setDelta(updateTick);
		while (m_Running)
		{
            if (m_window->iscloseRequested() || OInputsManager::Manager()->isKeyPressed(GLFW_KEY_ESCAPE))
                m_Running = false;
            
            float beginRenderingTime = m_Timer->getTime();
            Update();
            updates++;
            Refresh();

            Render();
            frames++;
            
            processTime = m_Timer->getTime() - beginRenderingTime;
            
            int sleepTime = (int)((updateTick - processTime) * MS_IN_SECONDS);
            if (sleepTime > 0) {
                m_Timer->sleep(sleepTime);
            }


            m_Timer->setDelta(m_Timer->getTime() - beginRenderingTime);
#ifdef O_MODE_DEBUG
            tickCounter += m_Timer->getDelta();
            
            if (tickCounter >= 1.0f) {
                m_FramesPerSecond = frames;
                m_UpdatesPerSecond = updates;
                
                frames = 0;
                updates = 0;
                tickCounter = 0;
                
                Tick();
            }
#endif


		}
	}
	
}