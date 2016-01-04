#include "OShader.h"
#include <Core/Utils/ShaderUtils.h>

NS_O_BEGIN

//	OShader::OShader(const char* name, const char* vertSrc, const char* fragSrc)
//		: m_Name(name), m_VertSrc(vertSrc), m_FragSrc(fragSrc)
//	{
//        Load(m_VertSrc, m_FragSrc);
//	}


OShader::~OShader()
{
    OLog("Shader : "<<m_Name << " deleted !");
    SAFE_DELETE(m_program);
}

GLuint OShader::load(const std::string & vertSrc, const std::string & fragSrc)
{

    GLuint vertexShader = ShaderUtils::createShaderFromString(vertSrc.c_str(), GL_VERTEX_SHADER);
    GLuint fragmentShader = ShaderUtils::createShaderFromString(fragSrc.c_str(), GL_FRAGMENT_SHADER);
    
    m_program = new Program(vertexShader, fragmentShader);
    
    bindLocations();
    
    m_program->link();
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return 0;
}

GLint OShader::GetUniformLocation(const GLchar* name)
{
    GLint result = m_program->GetUniform(name);
		if (result == -1)
			OErrLog(m_Name << ": could not find uniform "<< name << " in Shader!");

    return result;
}

void OShader::setUniform1f(const GLchar* name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void OShader::setUniform1fv(const GLchar* name, float* value, int count)
{
    glUniform1fv(GetUniformLocation(name), count, value);
}

void OShader::setUniform1i(const GLchar* name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void OShader::setUniform1iv(const GLchar* name, int* value, int count)
{
    glUniform1iv(GetUniformLocation(name), count, value);
}

void OShader::setUniform2f(const GLchar* name, const maths::vec2& vector)
{
    glUniform2f(GetUniformLocation(name), vector.x, vector.y);
}

void OShader::setUniform3f(const GLchar* name, const maths::vec3& vector)
{
    glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
}

void OShader::setUniform4f(const GLchar* name, const maths::vec4& vector)
{
    glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void OShader::setUniformMat3(const GLchar* name, const maths::mat3& mat)
{
    glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, mat.mat);
}

void OShader::setUniformMat4(const GLchar* name, const maths::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.mat);
}

void OShader::bind() const
{
    m_program->Bind();
}

void OShader::unbind() const
{
    m_program->Unbind();
}

NS_O_END