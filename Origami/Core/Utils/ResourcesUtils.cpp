#include "ResourcesUtils.h"
#include <Core/Utils/OLog.h>

#include <sstream>
#include <fstream>

#ifdef __APPLE__
#import <Foundation/Foundation.h>
#elif __ANDROID__
#include <android/asset_manager.h>

extern AAssetManager *mgr;
#endif

NS_O_BEGIN

const std::string RESOURCES_FOLDER = "AppData";

const char* ResourcesUtils::getResourcePathforFile(const char * file) {
#ifdef __APPLE__
	NSBundle* mainBundle = [NSBundle mainBundle];

	if (mainBundle != nil)
	{
		NSString *resourcesFolder = [NSString stringWithCString : RESOURCES_FOLDER.c_str() encoding : NSUTF8StringEncoding];
		NSString *fullPathS = [NSString stringWithFormat : @"%@/%@",resourcesFolder, [NSString stringWithUTF8String : file]];

		const char* fullPath = [[mainBundle pathForResource : fullPathS ofType : nil] UTF8String];
		return fullPath;
	}
	return NULL;
#elif __ANDROID__
	return file;
#else
	std::string outp = RESOURCES_FOLDER + '\\' + file;
	return outp.c_str();
#endif
}

bool ResourcesUtils::doesFileExists(const char * file)
{
#ifdef __ANDROID__
    AAsset* aa = AAssetManager_open(mgr, file, AASSET_MODE_UNKNOWN);
    bool fileExists = false;
    if (aa)
    {
        fileExists = true;
        AAsset_close(aa);
    }
    return fileExists;
#else
    if (std::ifstream(ResourcesUtils::getResourcePathforFile(file))) {
        return true;
    }
    return false;
#endif
}

int ResourcesUtils::fileLength(const char * filePath, unsigned char *& buffer,
		size_t &buffer_length) {
#ifdef __ANDROID__

	if (!mgr)
		return 0;

	AAsset *fileAsset = AAssetManager_open(mgr, filePath, AASSET_MODE_BUFFER);

	if (fileAsset != NULL) {
		buffer_length = AAsset_getLength(fileAsset);
		buffer = new unsigned char[buffer_length + 1];
		int32_t numBytes = AAsset_read(fileAsset, buffer, buffer_length);
		buffer[buffer_length] = '\0';

		AAsset_close(fileAsset);
	}

	return 1;
#else
	size_t bytes_read;
	FILE *f;
	f = fopen(getResourcePathforFile(filePath), "rb");

	if (NULL == f)
	{
		/*	the file doesn't seem to exist (or be open-able)	*/
		//        result_string_pointer = "Can not find DDS file";
		return 0;
	}
	fseek(f, 0, SEEK_END);
	buffer_length = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = (unsigned char *)malloc(buffer_length);
	if (NULL == buffer)
	{
		//        result_string_pointer = "malloc failed";
		fclose(f);
		return 0;
	}
	bytes_read = fread((void*)buffer, 1, buffer_length, f);
	fclose(f);
	if (bytes_read < buffer_length)
	{
		/*	huh?	*/
		buffer_length = bytes_read;
	}
#endif
	return 1;
}

NS_O_END
