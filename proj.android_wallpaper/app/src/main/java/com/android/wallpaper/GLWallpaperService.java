package com.android.wallpaper;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.InterstitialAd;
import com.medisoft.origamiwallpaper.R;

import android.content.Context;
import android.content.SharedPreferences;
import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;
import android.os.Handler;
import android.preference.PreferenceManager;
import android.service.wallpaper.WallpaperService;
import android.view.SurfaceHolder;



public abstract class GLWallpaperService extends WallpaperService {

	private InterstitialAd interstitial;
	private boolean adsDisabled;
	private String sDate;
	private Timer timer;
	Handler handler;

	public SharedPreferences loadPreferences()
	{
		SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
		adsDisabled = prefs.getBoolean("adsDisabled", false);
		sDate = prefs.getString("lastDate", "");
		return prefs;
	}

	public void displayInterstitial() {
		loadPreferences();
		
		SimpleDateFormat simpleDate =  new SimpleDateFormat("dd/MM/yyyy", java.util.Locale.getDefault());
		String currentDate = simpleDate.format(new Date());
		
	    if (interstitial.isLoaded() && !adsDisabled && !currentDate.equals(sDate)) {
	    	interstitial.show();
	      
	      	SharedPreferences.Editor editor = loadPreferences().edit();
	      	editor.putString("lastDate", currentDate);
			editor.commit();
	    }
	 }

	private void runOnUiThread(Runnable runnable) {
        handler.post(runnable);
    }

	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
		
		handler = new Handler();
		// Créez l'interstitiel.
	    interstitial = new InterstitialAd(this);
	    interstitial.setAdUnitId(getString(R.string.interstitial_ad_unit_id));
	    AdRequest adRequest = new AdRequest.Builder()
                .addTestDevice("64AA6E978D51F4F778648A6643AC4CD7")
                .build();

	    interstitial.loadAd(adRequest);
        
	    timer = new Timer();
	    timer.scheduleAtFixedRate(new TimerTask() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				runOnUiThread(new Runnable() {

					@Override
					public void run() {
						// TODO Auto-generated method stub
						displayInterstitial();
					}
				});
			}
		}, 10000, 60000);

	}
	public class GLEngine extends Engine {

		private WallpaperGLSurfaceView glSurfaceView;
		private boolean rendererHasBeenSet;

		@Override
		public void onCreate(SurfaceHolder surfaceHolder) {
		    super.onCreate(surfaceHolder);

		    glSurfaceView = new WallpaperGLSurfaceView(GLWallpaperService.this);
		    glSurfaceView.setPreserveEGLContextOnPause(true);
		}

		@Override
		public void onDestroy() {
		    super.onDestroy();
		    glSurfaceView.onDestroy();
		}

		protected void setRenderer(Renderer renderer) {
		    glSurfaceView.setRenderer(renderer);
		    rendererHasBeenSet = true;
		}

		protected void setEGLContextClientVersion(int version) {
		    glSurfaceView.setEGLContextClientVersion(version);
		}

		protected void setPreserveEGLContextOnPause(boolean preserve) {
		    glSurfaceView.setPreserveEGLContextOnPause(preserve);
		}
		
		protected void setEGLContextFactory(GLSurfaceView.EGLContextFactory cFactory)
		{
			glSurfaceView.setEGLContextFactory(cFactory);
		}
		
		protected void setEGLConfigChooser(GLSurfaceView.EGLConfigChooser cChooser)
		{
			glSurfaceView.setEGLConfigChooser(cChooser);
		}
		
		@Override
		public void onVisibilityChanged(boolean visible) {
		    super.onVisibilityChanged(visible);

		    if (rendererHasBeenSet) {
		        if (visible) {
		            glSurfaceView.onResume();
		        } else {
		            glSurfaceView.onPause();
		        }
		    }
		}

		class WallpaperGLSurfaceView extends GLSurfaceView {

		    WallpaperGLSurfaceView(Context context) {
		        super(context);
		    }

		    @Override
		    public SurfaceHolder getHolder() {
		        return getSurfaceHolder();
		    }

		    public void onDestroy() {
		        super.onDetachedFromWindow();
		    }
		}
	}

}
