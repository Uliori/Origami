#pragma once

#include <Core/Utils/OGLUtils.h>

namespace Origami {
    class Program
    {
        GLuint m_shaderProgram;
    public:
        
        Program(const GLuint vertexShader, const GLuint fragmentShader)
        {
            m_shaderProgram = glCreateProgram();
            glAttachShader(m_shaderProgram, vertexShader);
            glAttachShader(m_shaderProgram, fragmentShader);
        }
        
        ~Program()
        {
            glDeleteProgram(m_shaderProgram);
        }
        
        void link()
        {
            glLinkProgram(m_shaderProgram);
            
            GLint linkStatus;
            glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &linkStatus);
            if (linkStatus != GL_TRUE) {
                OErrLog("Program Link Failed");
                
                
                GLint infosLogLength;
                glGetProgramiv(m_shaderProgram, GL_INFO_LOG_LENGTH, &infosLogLength);
                GLchar *infoLog = new GLchar[infosLogLength + 1];
                glGetProgramInfoLog(m_shaderProgram, infosLogLength + 1, NULL, infoLog);
                OErrLog(infoLog);
                delete []infoLog;
            }
        }
        
        void Bind() const
        {
            glUseProgram(m_shaderProgram);
        }
        
        void Unbind() const
        {
            glUseProgram(0);
        }
        
        void BindLocation(GLuint index, const GLchar *name)
        {
            glBindAttribLocation(m_shaderProgram, index, name);
        }
        
        GLuint GetUniform(const GLchar *name)
        {
            return glGetUniformLocation(m_shaderProgram, name);
        }
    };
}

