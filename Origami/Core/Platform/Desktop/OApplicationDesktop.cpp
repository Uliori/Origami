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
        const float     DESIRED_FRAMETIME  = MS_IN_SECONDS / m_PreferredFramesPerSecond;
        const int       MAX_PHYSICS_STEPS  = 10;
        
        unsigned int    frames             = 0;
        unsigned int    updates            = 0;
        
        
        double previousTicks = m_Timer->getTime();
        
		while (m_Running)
		{
            if (m_window->iscloseRequested() || OInputsManager::Manager()->isKeyPressed(GLFW_KEY_ESCAPE))
                m_Running = false;
            
            double newTicks = m_Timer->getTime();
            int   loops = 0;
            float interpolation = 1;
            
            while (m_Timer->getTime() > previousTicks && loops < MAX_PHYSICS_STEPS) {
                Update(DESIRED_FRAMETIME / MS_IN_SECONDS);
                previousTicks += DESIRED_FRAMETIME;
                updates ++;
                loops++;
            }
            
            Refresh();

            interpolation = float( m_Timer->getTime() + DESIRED_FRAMETIME - previousTicks )/ float( DESIRED_FRAMETIME );
            Render(interpolation);
            frames++;
            
        
#ifdef O_MODE_DEBUG
            tickCounter += m_Timer->getTime() - newTicks;
            if (tickCounter >= MS_IN_SECONDS) {
                m_FramesPerSecond = frames;
                m_UpdatesPerSecond = updates;

                frames = 0;
                updates = 0;
                tickCounter -= MS_IN_SECONDS;

                Tick();
            }
#endif


		}
	}
	
}