#pragma once

//#ifdef O_TARGET_DESKTOP
#include <chrono>
#include <thread>

namespace Origami
{
	class OTimer
	{
	private:
		typedef std::chrono::system_clock		clock;
		typedef std::chrono::milliseconds  		milliseconds_type;

	public:

		OTimer()
		{
		}

        double getTime()
        {
            return std::chrono::duration_cast<milliseconds_type>(clock::now().time_since_epoch()).count();
        }

        void sleep(int milliseconds)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        }
	};
}
//#else
//#include <unistd.h>
//#include <time.h>
//
//namespace Origami
//{
//    class OTimer
//    {
//
//    public:
//
//        OTimer()
//        {
//        }
//
//        double getTime()
//        {
//        	struct timespec res;
//        	clock_gettime(CLOCK_MONOTONIC, &res);
//        	return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;
//        }
//
//        void sleep(int milliseconds)
//        {
//            usleep(milliseconds * 1000);
//        }
//    };
//}
//#endif
