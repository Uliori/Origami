package com.android.ads;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.medisoft.origamiwallpaper.R;

import android.content.Context;
import android.preference.Preference;
import android.util.AttributeSet;
import android.view.View;
import android.view.ViewGroup;

public class AdPreference extends Preference {

    public AdPreference(Context context, AttributeSet attrs, int defStyle) {super    (context, attrs, defStyle);}
    public AdPreference(Context context, AttributeSet attrs) {super(context, attrs);}
    public AdPreference(Context context) {super(context);}

    @Override
    protected View onCreateView(ViewGroup parent) {
        // this will create the linear layout defined in ads_layout.xml
        View view = super.onCreateView(parent);
     // Load an ad into the AdMob banner view.
        AdView adView = (AdView) view.findViewById(R.id.adView);
        AdRequest adRequest = new AdRequest.Builder()
                .addTestDevice("64AA6E978D51F4F778648A6643AC4CD7").build();
        adView.loadAd(adRequest);
        
        return view;    
    }
}