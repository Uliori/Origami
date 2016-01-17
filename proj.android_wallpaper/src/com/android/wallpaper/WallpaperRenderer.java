package com.android.wallpaper;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Point;
import android.opengl.GLSurfaceView;
import android.preference.PreferenceManager;
import android.view.Display;
import android.view.WindowManager;

public class WallpaperRenderer implements GLSurfaceView.Renderer
{
	private Context m_context;
	private AssetManager mgr;
	public static int m_width, m_height;
	
	public WallpaperRenderer(Context context) {
		// TODO Auto-generated constructor stub
		m_context = context;
	}
	
	public AssetManager getAssetsManager()
	{
		if (mgr == null) {
			mgr = m_context.getResources().getAssets();
		}
		return mgr;
	}

	void createWallpaper()
	{
		GL2JNILib.setAssetManager(getAssetsManager());
    	WindowManager wm = (WindowManager) m_context.getSystemService(Context.WINDOW_SERVICE);
    	Display display = wm.getDefaultDisplay();
    	
    	Point size = new Point();
    	display.getSize(size);
    	m_width = size.x;
    	m_height = size.y;
    	
    	GL2JNILib.init(m_width, m_height);
    	
    	String scene = PreferenceManager.getDefaultSharedPreferences(m_context).getString("oWallpaper", "1");
		GL2JNILib.loadScene(scene);
	}
	
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		// TODO Auto-generated method stub
		createWallpaper();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		// TODO Auto-generated method stub
		GL2JNILib.setAssetManager(getAssetsManager());
    	GL2JNILib.resize(width, height);
    	
    	String scene = PreferenceManager.getDefaultSharedPreferences(m_context).getString("oWallpaper", "1");
		GL2JNILib.loadScene(scene);
	}
	
	@Override
	public void onDrawFrame(GL10 gl) {
		// TODO Auto-generated method stub
		GL2JNILib.step();
	}
}
