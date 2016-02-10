//
//  TextureUtils.h
//  Origami
//
//  Created by Sephiroth on 8/15/14.
//  Copyright (c) 2014 Sephiroth. All rights reserved.
//

#pragma once

#include <Core/Utils/OGLUtils.hpp>
#include <Core/Graphics/OTexture.hpp>
#include <Core/ODirector.hpp>
#include <Core/OMacros.hpp>

NS_O_BEGIN
class TextureUtils {
public:
//			static GLuint loadTexture(const char * imagepath);
    static OTexture* loadTexture(const char * imagepath, bool invert_y = true, GLint param_W_S = GL_CLAMP_TO_EDGE, GLint param_W_T = GL_CLAMP_TO_EDGE);
    static void reloadTexture(OTexture* texture, const char * imagepath, bool invert_y = true);
    static void getFileName(const char * imagepath, std::string &fileName, int &scale);

    static GLuint loadTextureCube(const char* PosXFilename,
        const char* NegXFilename,
        const char* PosYFilename,
        const char* NegYFilename,
        const char* PosZFilename,
        const char* NegZFilename);

    static GLuint makeTexture(GLsizei width, GLsizei height, GLint internalformat, GLenum format, GLenum type, GLint param_MAG, GLint param_MIN, GLint param_W_S, GLint param_W_T);
};

NS_O_END
