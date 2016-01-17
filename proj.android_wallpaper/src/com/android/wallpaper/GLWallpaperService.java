package com.android.wallpaper;

//import java.util.Timer;
//import java.util.TimerTask;
//import android.os.Handler;
//import android.preference.PreferenceManager;
//import android.content.SharedPreferences;
//import com.google.android.gms.ads.AdListener;
//import com.google.android.gms.ads.AdRequest;
//import com.google.android.gms.ads.InterstitialAd;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;
import android.service.wallpaper.WallpaperService;
import android.view.SurfaceHolder;



public abstract class GLWallpaperService extends WallpaperService {
	
//	public static int width;
//	public static int height;
//	private static InterstitialAd interstitial;
//	private static Timer timer;
//	Handler handler;
//	
//	//Preferences Stuffs
//
//	public static GLWallpaperService sharedS;
//	public static SharedPreferences getPreferences()
//	{
//		SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(sharedS);
//		
//		 //Créez la demande d'annonce.
//		if (showads) {
//		    AdRequest adRequest = new AdRequest.Builder().addTestDevice("46050842480CEB09AE1819558FF42F79").build();
//		    interstitial.setAdListener(new AdListener() {});
//		    interstitial.loadAd(adRequest);			
//		}
//		return prefs;
//	}
//	
//	public void displayInterstitial() {
//		Log.e("Ads", "Display Method");
//	    if (interstitial.isLoaded() && showads) {
//	      interstitial.show();
//	    }
//	 }
	
//	private void runOnUiThread(Runnable runnable) {
//        handler.post(runnable);
//    }
	
	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
//		sharedS = this;
//		handler = new Handler();
//		// Créez l'interstitiel.
//	    interstitial = new InterstitialAd(this);
//	    interstitial.setAdUnitId("ca-app-pub-1060148675448438/5428665900");
//	    timer = new Timer();
//	    timer.scheduleAtFixedRate(new TimerTask() {
//			
//			@Override
//			public void run() {
//				// TODO Auto-generated method stub
//				runOnUiThread(new Runnable() {
//					
//					@Override
//					public void run() {
//						// TODO Auto-generated method stub
//						displayInterstitial();
//					}
//				});
//			}
//		}, 10000, 60000);
	    
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