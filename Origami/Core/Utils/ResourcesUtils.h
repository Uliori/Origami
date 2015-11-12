#pragma once

#include <stdio.h>
#include <string>

namespace Origami {
		class ResourcesUtils {
		public:
			static std::string s_PackageName;
			static std::string s_ExternalStorage;

			static const char* getResourcePathforFile(const char * file);
			static FILE * openFile(const char * file);
			static int fileLength(FILE* f, unsigned char *& buffer, size_t &buffer_length);
		};
}




