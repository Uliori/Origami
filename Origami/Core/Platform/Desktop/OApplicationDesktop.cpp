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
        double          tickCounter        = 0;
        
        const float     MS_IN_SECONDS      = 1000.0f;
        const float     DESIRED_FRAMETIME  = 1.0f / m_PreferredFramesPerSecond;
        const int       MAX_PHYSICS_STEPS  = 10;
        
        unsigned int    frames             = 0;
        unsigned int    updates            = 0;
        
        
        float previousTicks = m_Timer->getTime();
        //TODO : this is not optimal, check for optimizations !!
        
		while (m_Running)
		{
            if (m_window->iscloseRequested() || OInputsManager::Manager()->isKeyPressed(GLFW_KEY_ESCAPE))
                m_Running = false;
            
            float newTicks = m_Timer->getTime();
            int i = 0;
            while (newTicks > previousTicks && i < MAX_PHYSICS_STEPS) {
                Update(DESIRED_FRAMETIME);
                previousTicks += DESIRED_FRAMETIME;
                updates ++;
                i++;
            }
            
            Refresh();

            //TODO : Add interpolation for rendering. http://www.koonsolo.com/news/dewitters-gameloop/
            Render();
            frames++;
            
            while (((DESIRED_FRAMETIME - (m_Timer->getTime() - newTicks)) * MS_IN_SECONDS) > 0.0f) {
                m_Timer->sleep(1);
            }
            
#ifdef O_MODE_DEBUG
            tickCounter += m_Timer->getTime() - newTicks;

            if (tickCounter >= 1.0f) {
                m_FramesPerSecond = frames;
                m_UpdatesPerSecond = updates;

                frames = 0;
                updates = 0;
                tickCounter -= 1.0f;

                Tick();
            }
#endif


		}
	}
	
}