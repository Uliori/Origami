#pragma once

#include "OGame.hpp"
#include <Core/ODirector.h>
#include <Core/Utils/OResourceManager.h>

class Game {

private:
  static Game *s_jGame;
  OGame *s_game = nullptr;
  uint g_width;
  uint g_height;

  const float  MS_IN_SECOND	      = 1000.0f;
  double       tickCounter        = 0;
  float     	 DESIRED_FRAMETIME  = 0;
  const int    MAX_PHYSICS_STEPS  = 10;
  unsigned int frames             = 0;
  unsigned int updates            = 0;
  double 			 previousTicks	    = 0;
  double       accumulator  = 0;

public:
  Game();
  virtual ~Game();

  static Game* instance();

  void init(int width, int height);
  void resize(int width, int height);
  void step();
  void setPaused(bool paused);
  void cleanUp();
  void loadScene(std::string scene);

private:
  void createGame();
  OGame* game();
};
