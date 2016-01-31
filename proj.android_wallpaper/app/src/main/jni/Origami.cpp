#include <jni.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <string>
#include "Game.hpp"

extern "C" {
JNIEXPORT void JNICALL Java_com_android_wallpaper_GL2JNILib_init(JNIEnv *env, jclass type, jint width, jint height);
JNIEXPORT void JNICALL Java_com_android_wallpaper_GL2JNILib_resize(JNIEnv *env, jclass type, jint width, jint height);
JNIEXPORT void JNICALL Java_com_android_wallpaper_GL2JNILib_setPaused(JNIEnv *env, jclass type, jboolean paused);
JNIEXPORT void JNICALL Java_com_android_wallpaper_GL2JNILib_step(JNIEnv *env, jclass type);
JNIEXPORT void JNICALL Java_com_android_wallpaper_GL2JNILib_cleanUp(JNIEnv *env, jclass type);
JNIEXPORT void JNICALL Java_com_android_wallpaper_GL2JNILib_setAssetManager(JNIEnv *env, jobject obj, jobject assetManager);
JNIEXPORT void JNICALL Java_com_android_wallpaper_GL2JNILib_loadScene(JNIEnv *env, jclass type, jstring scene);
AAssetManager *mgr;
};

JNIEXPORT void JNICALL
Java_com_android_wallpaper_GL2JNILib_init(JNIEnv *env, jclass type, jint width, jint height)
{
	Game::instance()->init(width, height);
}

JNIEXPORT void JNICALL
Java_com_android_wallpaper_GL2JNILib_resize(JNIEnv *env, jclass type, jint width, jint height)
{
	Game::instance()->resize(width, height);
}

JNIEXPORT void JNICALL
Java_com_android_wallpaper_GL2JNILib_setPaused(JNIEnv *env, jclass type, jboolean paused)
{
	Game::instance()->setPaused(paused);
}

JNIEXPORT void JNICALL
Java_com_android_wallpaper_GL2JNILib_step(JNIEnv *env, jclass type) {
	Game::instance()->step();
}

JNIEXPORT void JNICALL Java_com_android_wallpaper_GL2JNILib_loadScene(JNIEnv *env, jclass type, jstring scene)
{
	const char * path = env->GetStringUTFChars(scene , NULL);
	Game::instance()->loadScene(std::string(path));
}

JNIEXPORT void JNICALL Java_com_android_wallpaper_GL2JNILib_setAssetManager(JNIEnv *env, jobject obj, jobject assetManager)
{
	mgr = AAssetManager_fromJava(env, assetManager);
}

JNIEXPORT void JNICALL Java_com_android_wallpaper_GL2JNILib_cleanUp(JNIEnv *env, jclass type)
{
	Game::instance()->cleanUp();
}
