#pragma once

#include "program.h"

#include <Core/OGL.h>
#include <Core/Maths/OMaths.h>

#include <string>

namespace Origami {
    
	class OShader
	{
	protected:
		const char* m_Name;
        
        Program *m_program;
        
	public:
//        OShader(const char* name, const char* vertSrc, const char* fragSrc);
		virtual ~OShader();

		void SetUniform1f(const GLchar* name, float value);
		void SetUniform1fv(const GLchar* name, float* value, int count);
		void SetUniform1i(const GLchar* name, int value);
		void SetUniform1iv(const GLchar* name, int* value, int count);
		void SetUniform2f(const GLchar* name, const maths::vec2& vector);
		void SetUniform3f(const GLchar* name, const maths::vec3& vector);
        void SetUniform4f(const GLchar* name, const maths::vec4& vector);
        void SetUniformMat3(const GLchar* name, const maths::mat3& matrix);
		void SetUniformMat4(const GLchar* name, const maths::mat4& matrix);

        GLint GetUniformLocation(const GLchar* name);
        
		void Bind() const;
		void Unbind() const;
        
        virtual void BindLocations() = 0;
	protected:
		GLuint Load(const std::string &vertSrc, const std::string &fragSrc);
		
	};

}