package com.liongamestudio.origamiwallpaper;

import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.os.Bundle;
import android.preference.PreferenceActivity;
import android.preference.PreferenceFragment;

public class WallpaperPreferencesActivity extends PreferenceActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		// Display the fragment as the main content.
				FragmentManager mFragmentManager = getFragmentManager();
				FragmentTransaction mFragmentTransaction = mFragmentManager
						.beginTransaction();
				PrefsFragment mPrefsFragment = new PrefsFragment();
				mFragmentTransaction.replace(android.R.id.content, mPrefsFragment);
				mFragmentTransaction.commit();
	}

	 public static class PrefsFragment extends PreferenceFragment {
	        @Override
	        public void onCreate(Bundle savedInstanceState) {
	            super.onCreate(savedInstanceState);

	            // Load the preferences from an XML resource
	            addPreferencesFromResource(R.xml.preference);
	        }
	}
}
