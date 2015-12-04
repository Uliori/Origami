#pragma once

#ifdef O_TARGET_DESKTOP
#include <chrono>
#include <thread>

namespace Origami
{
	class OTimer
	{
	private:
		typedef std::chrono::high_resolution_clock		   clock; //
		typedef std::chrono::milliseconds          milliseconds_type;

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
#else
#include <sys/time.h>
#include <unistd.h>

namespace Origami
{
    class OTimer
    {
        
    public:
        
        OTimer()
        {
        }
        
        double getTime()
        {
            struct timeval tv;
            gettimeofday(&tv, 0);
            return unsigned((tv.tv_sec * 1000.0f) + (tv.tv_usec / 1000.0f));
        }
        
        void sleep(int milliseconds)
        {
            usleep(milliseconds * 1000);
        }
    };
}
#endif