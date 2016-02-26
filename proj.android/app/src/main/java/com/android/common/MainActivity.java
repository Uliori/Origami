package com.android.common;

public class MainActivity extends android.app.NativeActivity {
    static {
//        System.loadLibrary("box2d_static");
//        System.loadLibrary("soil2");
//        System.loadLibrary("freetype2");
        System.loadLibrary("origami");
    }
}