#include <jni.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "OGame.hpp"
#include <Core/Utils/OResourceManager.h>

extern "C" {
JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv *env, jclass type, jint width, jint height);
JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv *env, jclass type);
JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_setAssetManager(JNIEnv *env, jobject obj, jobject assetManager);
AAssetManager *mgr;
};

OGame *s_game = nullptr;
uint g_width;
uint g_height;
const float 	MS_IN_SECOND	   = 1000.0f;
double          tickCounter        = 0;
float     		DESIRED_FRAMETIME  = 0;
const int       MAX_PHYSICS_STEPS  = 10;
unsigned int    frames             = 0;
unsigned int    updates            = 0;
float 			previousTicks = 0;

OGame *game()
{
	if (s_game == nullptr) {
		s_game = new OGame("", g_width, g_height);
	}
	return s_game;
}


JNIEXPORT void JNICALL
Java_com_android_gl2jni_GL2JNILib_init(JNIEnv *env, jclass type, jint width, jint height) {
	g_width = width;
	g_height = height;

	game()->Start();
	DESIRED_FRAMETIME = 1.0f / game()->GetPreferredFPS();
	previousTicks = game()->getTimer()->getTime();

	OResourceManager::checkResources();

}

JNIEXPORT void JNICALL
Java_com_android_gl2jni_GL2JNILib_step(JNIEnv *env, jclass type) {

	float newTicks = game()->getTimer()->getTime();
	int   loops = 0;
	float interpolation = 1;

	while (game()->getTimer()->getTime() > previousTicks && loops < MAX_PHYSICS_STEPS) {
		game()->Update(DESIRED_FRAMETIME);
		previousTicks += DESIRED_FRAMETIME;
		updates ++;
		loops++;
	}

	game()->Refresh();

	interpolation = float( game()->getTimer()->getTime() + DESIRED_FRAMETIME - previousTicks )/ float( DESIRED_FRAMETIME );
	game()->Render(interpolation);
	frames++;


#ifdef O_MODE_DEBUG
	tickCounter += game()->getTimer()->getTime() - newTicks;
//	OLog(game()->getTimer()->getTime() - newTicks);
	if (tickCounter >= MS_IN_SECOND) {

		game()->setFPS(frames);
		game()->setUPS(updates);

		frames = 0;
		updates = 0;
		tickCounter -= MS_IN_SECOND;

		game()->Tick();
	}
#endif

}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_setAssetManager(JNIEnv *env, jobject obj, jobject assetManager)
{
	mgr = AAssetManager_fromJava(env, assetManager);
}

