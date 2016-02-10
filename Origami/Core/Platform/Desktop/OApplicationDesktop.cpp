#include <Core/App/OApplication.hpp>
#include <Core/Inputs/OInputsManager.hpp>

NS_O_BEGIN

OApplication::~OApplication()
{

    SAFE_DELETE(m_Window);

    OResourceManager::cleanUp();
    ORendererFactory::deleteRenderers();
    glfwTerminate();
}

void OApplication::run()
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
        if (m_Window->iscloseRequested() || OInputsManager::manager()->isKeyPressed(GLFW_KEY_ESCAPE))
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
                update(DESIRED_FRAMETIME / MS_IN_SECONDS);
                updates ++;
                refresh();
            }
        }

        float interpolation = float( ODirector::director()->getTimer()->getTime() + DESIRED_FRAMETIME - previousTicks )/ float( DESIRED_FRAMETIME );
        render(interpolation);
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
                tick();
        }
#endif
    }
}

NS_O_END
