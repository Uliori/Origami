#include "Game.hpp"

Game* Game::s_jGame = nullptr;

Game::Game()
{

}

Game::~Game()
{

}

Game* Game::instance()
{
  if (s_jGame == nullptr) {
    s_jGame = new Game();
  }
  return s_jGame;
}

void Game::createGame()
{
	if (s_game != nullptr) {
		// retain
		s_game->retain();
	}
	else
	{
		// initialize
		s_game = new OGame("", g_width, g_height);
	}
}

OGame* Game::game()
{
	if (s_game == nullptr) {
		createGame();
	}
	return s_game;
}

void Game::init(int width, int height)
{
  g_width = width;
  g_height = height;

  createGame();
  if (s_game->getReferenceCount() == 1) {
    s_game->start();
  }
  else
  {
     OResourceManager::checkResources();
  }

  DESIRED_FRAMETIME = MS_IN_SECOND / game()->getPreferredFPS();//
  previousTicks = ODirector::director()->getTimer()->getTime();
}

void Game::resize(int width, int height)
{
  g_width = width;
	g_height = height;

    if (ODirector::director()->getCurrentScene()) {
        ODirector::director()->setFrameSize(g_width, g_height);

        OSize designResolutionSize = ODirector::director()->getDesignResolutionSize();

        if (g_width > g_height) { //Landscape
            ODirector::director()->setDesignResolutionSize(MAX(designResolutionSize.width, designResolutionSize.height), MIN(designResolutionSize.width, designResolutionSize.height), ResolutionPolicy::FIXED_HEIGHT);
        }
        else
        {
            ODirector::director()->setDesignResolutionSize(MIN(designResolutionSize.width, designResolutionSize.height), MAX(designResolutionSize.width, designResolutionSize.height), ResolutionPolicy::FIXED_WIDTH);
        }


        OSize fS = ODirector::director()->getFrameSize();
        glViewport(0, 0, fS.width, fS.height);
    }
}

void Game::step()
{
  double startTicks =  ODirector::director()->getTimer()->getTime();
  double passedTime = startTicks - previousTicks;
  previousTicks = startTicks;


  if(!game()->isSupended()) {

    accumulator += passedTime;

    int   loops = 0;

    while(accumulator >= DESIRED_FRAMETIME && loops < MAX_PHYSICS_STEPS)
    {
      s_game->update(DESIRED_FRAMETIME / MS_IN_SECOND);
      accumulator -= DESIRED_FRAMETIME;
      updates ++;
      loops++;
    }
  }


  s_game->refresh();

  float interpolation = float(ODirector::director()->getTimer()->getTime() + DESIRED_FRAMETIME - previousTicks )/ float( DESIRED_FRAMETIME );
  s_game->render(interpolation);
  if(!s_game->isSupended()) { frames++; }

#ifdef O_MODE_DEBUG
     tickCounter += passedTime;
     if (tickCounter >= MS_IN_SECOND) {

       s_game->setFPS(frames);
       s_game->setUPS(updates);

       frames = 0;
       updates = 0;
       tickCounter -= MS_IN_SECOND;
       if(!s_game->isSupended()) {
         s_game->tick();
       }
     }
#endif
}

void Game::setPaused(bool paused)
{
  if (!s_game)
		return;

	if (paused) {
		s_game->suspend();
	}
	else
	{
    if (isDirty) {
      ODirector::director()->reloadCurrentScene();
      isDirty = false;
    }
		s_game->resume();
	}
}

void Game::setDirty()
{
  isDirty = true;
}

void Game::cleanUp()
{
  if (s_game) {
		int rc = s_game->getReferenceCount();
		s_game->release();
		if (rc == 1) {
			s_game = nullptr;
      SAFE_DELETE(s_jGame);
		}
	}
}
