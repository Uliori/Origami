#pragma once

#include <Core/OGL.h>
#include <Core/Utils/OLog.h>

#include <Core/OMacros.h>

NS_O_BEGIN

#ifdef O_MODE_DEBUG
	#define OGLCall(x)	glGetError();\
                        x; \
						OGLUtils::log_gl_call(#x, __FILE__, __LINE__);
#else
	#define OGLCall(x) \
                        x;
#endif

class OGLUtils
{
public:
	inline static void log_gl_call(const char* function, const char* file, int line)
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
            OErrLog("[OpenGL Error] " << ((error == GL_INVALID_ENUM) ? " Invalid enum" : (error == GL_INVALID_VALUE) ? " Invalid value" :(error == GL_INVALID_OPERATION) ? " Invalid operation" : "unknown error")<< " : " << error << " " << function << " " << file << ":" << line);
		}
	}

	inline static void printGLInfo(bool printExtensions = false) {
		OLog("OGL  Version : " << glGetString(GL_VERSION));
		OLog("GLSL Version : " << glGetString(GL_SHADING_LANGUAGE_VERSION));
		OLog("Vendor       : " << glGetString(GL_VENDOR));
		OLog("Renderer     : " << glGetString(GL_RENDERER));

		if (printExtensions) {
			OLog(glGetString(GL_EXTENSIONS));
		}
	}
};

NS_O_END
