#include <Core/App/OApplication.h>
#include <Core/Inputs/OInputsManager.h>

NS_O_BEGIN

OApplication::~OApplication()
{
    
    SAFE_DELETE(m_window);
    
    OResourceManager::cleanUp();
    ORendererFactory::deleteRenderers();
    glfwTerminate();
}

void OApplication::Run()
{
    double          tickCounter        = 0;
    
    const float     MS_IN_SECONDS      = 1000.0f;
    const float     DESIRED_FRAMETIME  = MS_IN_SECONDS / m_PreferredFramesPerSecond;
    const int       MAX_PHYSICS_STEPS  = 10;
    
    unsigned int    frames             = 0;
    unsigned int    updates            = 0;
    double          accumulator        = 0;
    
    double previousTicks = ODirector::director()->getTimer()->getTime();
    
    while (m_Running)
    {
        if (m_window->iscloseRequested() || OInputsManager::Manager()->isKeyPressed(GLFW_KEY_ESCAPE))
            m_Running = false;
        
        double startTicks =  ODirector::director()->getTimer()->getTime();
        double passedTime = startTicks - previousTicks;
        previousTicks = startTicks;
        
        
        if(!isSupended())
        {
            accumulator += passedTime;
            
            int   loops = 0;
            
            while (accumulator >= DESIRED_FRAMETIME && loops < MAX_PHYSICS_STEPS) {
                accumulator -= DESIRED_FRAMETIME;
                loops++;
                    Update(DESIRED_FRAMETIME / MS_IN_SECONDS);
                    updates ++;
            }
        }
        
        Refresh();

        
        float interpolation = float( ODirector::director()->getTimer()->getTime() + DESIRED_FRAMETIME - previousTicks )/ float( DESIRED_FRAMETIME );
        Render(interpolation);
        if(!isSupended()) {
            frames++;
        }
        
    
#ifdef O_MODE_DEBUG
        tickCounter += passedTime;
        if (tickCounter >= MS_IN_SECONDS) {
            m_FramesPerSecond = frames;
            m_UpdatesPerSecond = updates;

            frames = 0;
            updates = 0;
            tickCounter -= MS_IN_SECONDS;

            if(!isSupended())
                Tick();
        }
#endif


    }
}
	
NS_O_END