package com.android.gl2jni;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Point;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.Display;
import android.view.WindowManager;

public class RendererWrapper implements GLSurfaceView.Renderer {
	private Context m_context;
	private AssetManager mgr;
	public static int m_width, m_height;
	
	public AssetManager getAssetsManager()
	{
		if (mgr == null) {
			mgr = m_context.getResources().getAssets();
		}
		return mgr;
	}
	
	public RendererWrapper(Context context)
	{
		m_context = context;
	}

	@Override
    public void onDrawFrame(GL10 gl) {
        GL2JNILib.step();
    }
	
    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
    	GL2JNILib.setAssetManager(getAssetsManager());
    	GL2JNILib.resize(width, height);
    	
    	Log.i("Origami", "Changed");
    }
    
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
    	
    	Log.i("Origami", "Created");
    	
     	GL2JNILib.setAssetManager(getAssetsManager());
    	WindowManager wm = (WindowManager) m_context.getSystemService(Context.WINDOW_SERVICE);
    	Display display = wm.getDefaultDisplay();

    	Point size = new Point();
    	display.getSize(size);
    	m_width = size.x;
    	m_height = size.y;

    	GL2JNILib.init(m_width, m_height);

    }

}