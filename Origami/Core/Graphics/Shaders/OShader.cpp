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
    OLog("Shader : " << m_Name << " deleted !");
    SAFE_DELETE(m_Program);
}

GLuint OShader::load(const std::string & vertSrc, const std::string & fragSrc)
{

    GLuint vertexShader = ShaderUtils::createShaderFromString(vertSrc.c_str(), GL_VERTEX_SHADER);
    GLuint fragmentShader = ShaderUtils::createShaderFromString(fragSrc.c_str(), GL_FRAGMENT_SHADER);

    m_Program = new Program(vertexShader, fragmentShader);

    bindLocations();

    m_Program->link();

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return 0;
}

GLint OShader::getUniformLocation(const GLchar* name)
{
    GLint result = m_Program->getUniform(name);
		if (result == -1)
			OErrLog(m_Name << ": could not find uniform "<< name << " in Shader!");

    return result;
}

void OShader::setUniform1f(const GLchar* name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

void OShader::setUniform1fv(const GLchar* name, float* value, int count)
{
    glUniform1fv(getUniformLocation(name), count, value);
}

void OShader::setUniform1i(const GLchar* name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void OShader::setUniform1iv(const GLchar* name, int* value, int count)
{
    glUniform1iv(getUniformLocation(name), count, value);
}

void OShader::setUniform2f(const GLchar* name, const maths::vec2& vector)
{
    glUniform2f(getUniformLocation(name), vector.x, vector.y);
}

void OShader::setUniform3f(const GLchar* name, const maths::vec3& vector)
{
    glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
}

void OShader::setUniform4f(const GLchar* name, const maths::vec4& vector)
{
    glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void OShader::setUniformMat3(const GLchar* name, const maths::mat3& mat)
{
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, mat.mat);
}

void OShader::setUniformMat4(const GLchar* name, const maths::mat4& matrix)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.mat);
}

void OShader::bind() const
{
    m_Program->bind();
}

void OShader::unbind() const
{
    m_Program->unbind();
}

NS_O_END
