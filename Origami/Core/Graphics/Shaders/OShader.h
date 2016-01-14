#pragma once

#include "program.h"

#include <Core/OGL.h>
#include <Core/Maths/OMaths.h>

#include <string>

#include <Core/OMacros.h>

NS_O_BEGIN

class OShader
{
protected:
    const char* m_Name;

    Program* m_Program;

public:
//        OShader(const char* name, const char* vertSrc, const char* fragSrc);
    virtual ~OShader();



    void setUniform1f(const GLchar* name, float value);
    void setUniform1fv(const GLchar* name, float* value, int count);
    void setUniform1i(const GLchar* name, int value);
    void setUniform1iv(const GLchar* name, int* value, int count);
    void setUniform2f(const GLchar* name, const maths::vec2& vector);
    void setUniform3f(const GLchar* name, const maths::vec3& vector);
    void setUniform4f(const GLchar* name, const maths::vec4& vector);
    void setUniformMat3(const GLchar* name, const maths::mat3& matrix);
    void setUniformMat4(const GLchar* name, const maths::mat4& matrix);

    GLint getUniformLocation(const GLchar* name);

    void bind() const;
    void unbind() const;

    virtual void bindLocations() = 0;
    virtual void init() = 0;
protected:
    GLuint load(const std::string &vertSrc, const std::string &fragSrc);

};

NS_O_END
