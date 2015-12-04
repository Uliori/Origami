
//
//  OLog.h
//  Origami
//
//  Created by Sephiroth on 8/5/14.
//  Copyright (c) 2014 Sephiroth. All rights reserved.
//

#pragma once

#ifdef O_MODE_DEBUG
	#ifdef __ANDROID__
		#include <android/log.h>
		#include <string>
		#include <sstream>
		#include <iostream>
		#define OLog(msg)\
		{\
		std::stringstream ss;\
		ss << msg;\
		__android_log_write(ANDROID_LOG_VERBOSE, "Origami", ss.str().c_str()); \
		}

		#define OErrLog(msg)\
		{\
		std::stringstream ss;\
		ss << msg;\
		__android_log_write(ANDROID_LOG_ERROR, "Origami", ss.str().c_str()); \
		}
	#else
		#include <iostream>
		#define OLog(...) std::cout << __VA_ARGS__ << std::endl
		#define OErrLog(...) std::cerr << "WARNING : " << __VA_ARGS__ << std::endl
	#endif
#else
	#define OLog(...)
	#define OErrLog(...)
#endif
