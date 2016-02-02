/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.wallpaper;

import android.content.res.AssetManager;

// Wrapper for native library

public class GL2JNILib {

	static {
		System.loadLibrary("soil2");
//		System.loadLibrary("freetype2");
//		System.loadLibrary("harfbuzz");
        System.loadLibrary("origamiwallpaper");
    }

    /**
     * @param width the current view width
     * @param height the current view height
     */

    public synchronized static native void init(int width, int height);
    public synchronized static native void resize(int width, int height);
    public synchronized static native void step();
	public synchronized static native void loadScene(String scene);
    public synchronized static native void setPaused(boolean paused);
    public synchronized static native void cleanUp();
    public synchronized static native void setAssetManager(AssetManager mgr);



// 	public static native void touchB(float x, float y);
// 	public static native void touchM(float x, float y, int dx, int dy);
// 	public static native void touchE(float x, float y);

}
