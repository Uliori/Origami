//
//  OGL.h
//  Origami
//
//  Created by Sephiroth on 8/5/14.
//  Copyright (c) 2014 Sephiroth. All rights reserved.
//

#pragma once

//GL Imports
#if defined(O_TARGET_DESKTOP_OSX)
    #define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>
#elif defined(O_TARGET_DESKTOP_WIN32)
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#elif defined(O_TARGET_MOBILE_IOS)
    #ifdef O_USE_ES3
        #include <OpenGLES/ES3/gl.h>
        #include <OpenGLES/ES3/glext.h>
        #define glClearDepth glClearDepthf
    #else
        #include <OpenGLES/ES2/gl.h>
        #include <OpenGLES/ES2/glext.h>

        #define glBindVertexArray glBindVertexArrayOES
        #define glDeleteVertexArrays glDeleteVertexArraysOES
        #define glGenVertexArrays glGenVertexArraysOES

        #define GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES
        #define glClearDepth glClearDepthf

        #define GL_RED GL_RED_EXT

    #endif
#elif defined(O_TARGET_MOBILE_ANDROID)
    #ifdef O_USE_ES3
        #include <GLES3/gl3.h>
        #include <EGL/egl.h>
        #include <EGL/eglext.h>
        #define glClearDepth glClearDepthf
    #else
        #include <EGL/egl.h>
        #include <GLES2/gl2ext.h>

        #define glBindVertexArray ((PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress ( "glBindVertexArrayOES" ))
        #define glDeleteVertexArrays ((PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress ( "glDeleteVertexArraysOES" ))
        #define glGenVertexArrays ((PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress ( "glGenVertexArraysOES" ))

        #define GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES
        #define glClearDepth glClearDepthf
        #define GL_RED 0x1903
    #endif

#endif

//GLSL Values
#ifdef O_TARGET_DESKTOP
    #define OGL_LAYOUT(ind)                  "layout(location = " #ind ") "
    #define OGL_ATTR                         "in"
    #define OGL_VARYO                        "out"
    #define OGL_VARYI                        "in"
    #define OGL_TEXTURE                      "texture"
    #define OGL_TEXTURECUBE                  "texture"
    #define OGL_FragColor                    "fragColor"
    #define OGL_FragColorDec                 "out vec4 fragColor;\n"
    #define OGL_FragColorArrayDec(c)         "out vec4 fragColor[" #c "];"
    #define OGL_FragOutDec(ind, type, name)  "layout(location = " #ind ") out " #type " " #name ";\n"
    #define OGL_FragOut(ind, name)           "" #name
    #define OGL_FragOutA(ind)                "fragColor["#ind"]"
#else
    #define OGL_LAYOUT(ind)                  ""
    #define OGL_ATTR                         "attribute"
    #define OGL_VARYO                        "varying"
    #define OGL_VARYI                        "varying"
    #define OGL_TEXTURE                      "texture2D"
    #define OGL_TEXTURECUBE                  "textureCube"
    #define OGL_FragColor                    "gl_FragColor"
    #define OGL_FragColorDec                 ""
    #define OGL_FragColorArrayDec(c)         ""
    #define OGL_FragOutDec(ind, type, name)  ""
    #define OGL_FragOut(ind, name)           "gl_FragData["#ind"]"
    #define OGL_FragOutA(ind)                "gl_FragData["#ind"]"
#endif

//GLSL Header

#ifdef O_TARGET_DESKTOP
    #define GLSLHEADER "#version 330 core\n"
#else
    #ifdef O_USE_ES3
        #define GLSLHEADER "#version 300 es\n"
    #else
        #define GLSLHEADER "#version 100\n"
    #endif
#endif
