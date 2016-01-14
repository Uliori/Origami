#include <jni.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "OGame.hpp"
#include <Core/ODirector.h>
#include <Core/Utils/OResourceManager.h>

extern "C" {
JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv *env, jclass type, jint width, jint height);
JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_resize(JNIEnv *env, jclass type, jint width, jint height);
JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_setPaused(JNIEnv *env, jclass type, jboolean paused);
JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv *env, jclass type);
JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_cleanUp(JNIEnv *env, jclass type);
JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_setAssetManager(JNIEnv *env, jobject obj, jobject assetManager);
AAssetManager *mgr;
};

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


double accumulator  = 0;

void createGame()
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

OGame *game()
{
	if (s_game == nullptr) {
		createGame();
	}
	return s_game;
}


JNIEXPORT void JNICALL
Java_com_android_gl2jni_GL2JNILib_init(JNIEnv *env, jclass type, jint width, jint height) {
	g_width = width;
	g_height = height;

	createGame();
	if (s_game->getReferenceCount() == 1) {
		s_game->start();
	}
	else
	{
		 OResourceManager::reloadResources();
	}

	DESIRED_FRAMETIME = MS_IN_SECOND / game()->getPreferredFPS();//
	previousTicks = ODirector::director()->getTimer()->getTime();
}

JNIEXPORT void JNICALL
Java_com_android_gl2jni_GL2JNILib_resize(JNIEnv *env, jclass type, jint width, jint height) {
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

JNIEXPORT void JNICALL
Java_com_android_gl2jni_GL2JNILib_setPaused(JNIEnv *env, jclass type, jboolean paused)
{
	if (!s_game)
		return;

	if (paused) {
		s_game->suspend();
	}
	else
	{
		s_game->resume();
	}
}

JNIEXPORT void JNICALL
Java_com_android_gl2jni_GL2JNILib_step(JNIEnv *env, jclass type) {

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

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_setAssetManager(JNIEnv *env, jobject obj, jobject assetManager)
{
	mgr = AAssetManager_fromJava(env, assetManager);
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_cleanUp(JNIEnv *env, jclass type)
{
	if (s_game) {
		int rc = s_game->getReferenceCount();
		s_game->release();
		if (rc == 1) {
			s_game = nullptr;
		}
	}
}
