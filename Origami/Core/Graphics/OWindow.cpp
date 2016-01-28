#include "OWindow.h"
#include <Core/Inputs/OInputsManager.h>
NS_O_BEGIN

OWindow::OWindow(const char* title, uint width, uint height, OApplication *app)
    :m_Title(title), m_Width(width), m_Height(height), m_Closed(false), m_Application(app)
{

    if (!init()) {
        OErrLog("Window initialization failed !");
        return;
    }
    setVsync(true);

    refreshInput();
}

OWindow::~OWindow()
{
    platformClean();
    ODirector::deleteManager();
}

bool OWindow::init()
{
    if (!platformInit()) {
        OErrLog("Platform initialization failed !");
        return false;
    }

    ODirector::director()->setFrameSize(m_Width, m_Height);
    ODirector::director()->loadGame();

    return true;
}

void OWindow::setDimensions(uint width, uint height) {

    m_Width = width;
    m_Height = height;

    ODirector::director()->setFrameSize(m_Width, m_Height);
}

bool OWindow::closed() const
{
    return m_Closed;
}

void OWindow::setVsync(bool enabled)
{
    m_Vsync = enabled;
    platformVsync(m_Vsync);
}

void OWindow::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OWindow::swapBuffers()
{
    platformUpdate();
}

void OWindow::refreshInput()
{
    OInputsManager::manager()->update();
}
NS_O_END
