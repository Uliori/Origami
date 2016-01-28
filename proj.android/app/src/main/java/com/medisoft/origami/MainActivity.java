package com.medisoft.origami;

public class MainActivity extends android.app.NativeActivity {
    static {
        System.loadLibrary("soil2");
        System.loadLibrary("origami");
    }
}