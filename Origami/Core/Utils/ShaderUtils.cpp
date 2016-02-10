//
//  ShaderUtils.cpp
//  Katana
//
//  Created by Sephiroth on 5/11/14.
//  Copyright (c) 2014 Sephiroth. All rights reserved.
//

#include "ShaderUtils.hpp"
#include "ResourcesUtils.hpp"

#include <fstream>
#include <streambuf>
#include <string>

NS_O_BEGIN

const GLchar* ShaderUtils::loadTextFromFile(const GLchar * path) {
    std::ifstream fin;
    fin.open(path);

    if (!fin.is_open()) {
        fin.close();
        OErrLog("File not found : '" << path << "'");
        return 0;
    }
    std::string source((std::istreambuf_iterator<GLchar>(fin)), std::istreambuf_iterator<GLchar>());
    fin.close();

    const GLchar *shaderSource = source.c_str();

    return shaderSource;
}

GLuint ShaderUtils::createShaderFromFile(const GLchar * path, GLenum shaderType) {

    GLuint shaderID = glCreateShader(shaderType);
    std::ifstream fin;
    fin.open(path);//getResourcePathforFile(

    if (!fin.is_open()) {
        fin.close();
        OErrLog("File not found : '" << path << "'");
        return 0;
    }
    std::string source((std::istreambuf_iterator<GLchar>(fin)), std::istreambuf_iterator<GLchar>());
    fin.close();

    const GLchar *shaderSource = source.c_str();
    //    NSString *file = [NSString stringWithUTF8String:];
    //    const GLchar *shaderSource = (GLchar *)[[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil] UTF8String];
    glShaderSource(shaderID, 1, &shaderSource, NULL);

    glCompileShader(shaderID);

    GLint compileStatus;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        OErrLog("Shader Failed to compile : '" << path << "'");


        GLint infosLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infosLogLength);
        GLchar *infoLog = new GLchar[infosLogLength + 1];
        glGetShaderInfoLog(shaderID, infosLogLength + 1, NULL, infoLog);
        OErrLog(std::string(infoLog));
        delete[]infoLog;

        return 0;
    }

    return shaderID;
}

GLuint ShaderUtils::createShaderFromString(const GLchar *shaderSource, GLenum shaderType) {
    GLuint shaderID = glCreateShader(shaderType);

    glShaderSource(shaderID, 1, &shaderSource, NULL);

    glCompileShader(shaderID);

    GLint compileStatus;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        OLog("Shader Failed to compile : '" << shaderSource << "'");

        GLint infosLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infosLogLength);
        GLchar *infoLog = new GLchar[infosLogLength + 1];
        glGetShaderInfoLog(shaderID, infosLogLength + 1, NULL, infoLog);
        OLog(std::string(infoLog));
        delete[]infoLog;

        return 0;
    }
    return shaderID;
}

//Creation de programme
GLuint ShaderUtils::createProgramFromShaders(const GLuint vertexShader, const GLuint fragmentShader) {
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    return shaderProgram;
}

GLuint ShaderUtils::linkProgram(const GLuint program)
{
    glLinkProgram(program);



    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        OErrLog("Program Link Failed");


        GLint infosLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infosLogLength);
        GLchar *infoLog = new GLchar[infosLogLength + 1];
        glGetProgramInfoLog(program, infosLogLength + 1, NULL, infoLog);
        OErrLog(infoLog);
        delete[]infoLog;

        return 0;
    }

    return program;

}

NS_O_END
