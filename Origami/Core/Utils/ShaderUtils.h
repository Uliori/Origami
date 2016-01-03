#pragma once

#include <Core/Utils/OGLUtils.h>

#include <Core/OMacros.h>

NS_O_BEGIN
class ShaderUtils {
public:
    static const GLchar* loadTextFromFile(const GLchar * path);

    //Creation de shaders
    static GLuint createShaderFromFile(const GLchar * path, GLenum shaderType);
    static GLuint createShaderFromString(const GLchar *shaderSource, GLenum shaderType);

    //Creation de programme
    static GLuint createProgramFromShaders(const GLuint vertexShader, const GLuint fragmentShader);
    static GLuint linkProgram(const GLuint program);
};

NS_O_END



