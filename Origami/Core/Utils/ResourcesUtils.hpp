#pragma once

#include <stdio.h>
#include <string>

#include <Core/OMacros.hpp>

NS_O_BEGIN
class ResourcesUtils {
public:
    static std::string s_PackageName;
    static std::string s_ExternalStorage;

    static const char* getResourcePathforFile(const char * file);
    static bool doesFileExists(const char * file);
    static int fileLength(const char * filePath, unsigned char *& buffer, size_t &buffer_length);
};
NS_O_END




