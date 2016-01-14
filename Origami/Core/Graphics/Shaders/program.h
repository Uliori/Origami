#pragma once

#include <Core/Utils/OGLUtils.h>

#include <Core/OMacros.h>

NS_O_BEGIN
class Program
{
    GLuint m_ShaderProgram;
public:

    Program(const GLuint vertexShader, const GLuint fragmentShader)
    {
        m_ShaderProgram = glCreateProgram();
        glAttachShader(m_ShaderProgram, vertexShader);
        glAttachShader(m_ShaderProgram, fragmentShader);
    }

    ~Program()
    {
        glDeleteProgram(m_ShaderProgram);
    }

    void link()
    {
        glLinkProgram(m_ShaderProgram);

        GLint linkStatus;
        glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            OErrLog("Program Link Failed");
            GLint infosLogLength;
            glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &infosLogLength);
            GLchar *infoLog = new GLchar[infosLogLength + 1];
            glGetProgramInfoLog(m_ShaderProgram, infosLogLength + 1, NULL, infoLog);
            OErrLog(infoLog);
            delete []infoLog;
        }
    }

    void bind() const
    {
        glUseProgram(m_ShaderProgram);
    }

    void unbind() const
    {
        glUseProgram(0);
    }

    void bindLocation(GLuint index, const GLchar *name)
    {
        glBindAttribLocation(m_ShaderProgram, index, name);
    }

    GLuint getUniform(const GLchar *name)
    {
        return glGetUniformLocation(m_ShaderProgram, name);
    }
};
NS_O_END
