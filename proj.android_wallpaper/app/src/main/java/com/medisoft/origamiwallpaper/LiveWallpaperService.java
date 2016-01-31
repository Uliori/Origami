package com.medisoft.origamiwallpaper;

import com.android.wallpaper.OpenGLES2WallpaperService;
import com.android.wallpaper.WallpaperRenderer;

import android.opengl.GLSurfaceView.Renderer;

public class LiveWallpaperService  extends OpenGLES2WallpaperService {
    @Override
	public Renderer getNewRenderer() {
    	return new WallpaperRenderer(LiveWallpaperService.this);
    }
}
