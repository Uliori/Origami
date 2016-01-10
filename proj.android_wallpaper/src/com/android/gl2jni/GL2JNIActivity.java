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

package com.android.gl2jni;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;


public class GL2JNIActivity extends Activity {

    GL2JNIView mView;

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        mView = new GL2JNIView(getApplication());
        mView.setPreserveEGLContextOnPause(true);
	    setContentView(mView);
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
        mView.setVisibility(View.GONE);
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
        mView.setVisibility(View.VISIBLE);
    }
    
    @Override
    protected void onDestroy() {
    	// TODO Auto-generated method stub
    	GL2JNILib.cleanUp();
    	super.onDestroy();
    }
}
