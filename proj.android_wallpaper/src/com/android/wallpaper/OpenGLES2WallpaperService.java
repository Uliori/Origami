package com.android.wallpaper;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView.Renderer;
import android.view.SurfaceHolder;

public abstract class OpenGLES2WallpaperService extends GLWallpaperService {
		
    @Override
    public Engine onCreateEngine() {
        return new OpenGLES2Engine();
    }
 
    class OpenGLES2Engine extends GLWallpaperService.GLEngine {
    	
        @Override
        public void onCreate(SurfaceHolder surfaceHolder) {
            super.onCreate(surfaceHolder);
 
            // Check if the system supports OpenGL ES 2.0.
            final ActivityManager activityManager =
                (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
            final ConfigurationInfo configurationInfo =
                activityManager.getDeviceConfigurationInfo();
            final boolean supportsEs2 =
                configurationInfo.reqGlEsVersion >= 0x20000;
 
            if (supportsEs2)
            {
                // Request an OpenGL ES 2.0 compatible context.
                setEGLContextClientVersion(2);
 
                // On Honeycomb+ devices, this improves the performance when
                // leaving and resuming the live wallpaper.
                setPreserveEGLContextOnPause(true);
 
                // Set the renderer to our user-defined renderer.
                setRenderer(getNewRenderer());
            }
            else
            {
                // This is where you could create an OpenGL ES 1.x compatible
                // renderer if you wanted to support both ES 1 and ES 2.
                return;
            }
        }
        
        @Override
        public void onSurfaceDestroyed(SurfaceHolder holder) {
        	// TODO Auto-generated method stub
        	super.onSurfaceDestroyed(holder);
        	GL2JNILib.cleanUp();
        }
        
        @Override
        public void onDestroy() {
        	// TODO Auto-generated method stub
        	super.onDestroy();
        }
        
        @Override
        public void onVisibilityChanged(boolean visible) {
        	// TODO Auto-generated method stub
        	super.onVisibilityChanged(visible);
        	
        	if (WallpaperRenderer.m_height != 0 && WallpaperRenderer.m_width != 0) {
        		GL2JNILib.setPaused(!visible);
			}
        }
    }
 
    public abstract Renderer getNewRenderer();
}