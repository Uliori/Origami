
#include "Embedded.hpp"

NS_O_BEGIN

	byte DEFAULT_FONT_ARRAY[] =
	{
#include "files/SourceSansPro-Light.embed"
	};

	byte* DEFAULT_FONT = DEFAULT_FONT_ARRAY;
	unsigned int DEFAULT_FONT_SIZE = sizeof(DEFAULT_FONT_ARRAY);
	
NS_O_END