#include "OWindow.h"
#include <Core/Inputs/OInputsManager.h>
NS_O_BEGIN

OWindow::OWindow(const char* title, uint width, uint height)
    :m_Title(title), m_Width(width), m_Height(height), m_Closed(false)
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
    ODirector::DeleteManager();
}

bool OWindow::init()
{
    if (!PlatformInit()) {
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
    ODirector::director()->updateCurrentScene(deltaTime);
}

void OWindow::render(float interpolation)
{
    ODirector::director()->renderCurrentScene(interpolation);
}

void OWindow::swapBuffers()
{
    PlatformUpdate();
}

void OWindow::refreshInput()
{
    OInputsManager::Manager()->update();
}
NS_O_END