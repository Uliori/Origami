#pragma once

#include <chrono>
#include <thread>

namespace Origami
{
	class OTimer
	{
	private:
		typedef std::chrono::high_resolution_clock  HighResolutionClock;
		typedef std::chrono::milliseconds           milliseconds_type;
        
//		std::chrono::time_point<HighResolutionClock> m_Start;
        
//        float m_delta;

	public:
        
		OTimer()
		{
//			Reset();
		}

//		void Reset()
//		{
//			m_Start = HighResolutionClock::now();
//		}
        
        float getTime()
        {
            return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now().time_since_epoch()).count() / 1000.0f;
        }
        
//        float getRunningTime()
//        {
//            return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - m_Start).count() / 1000.0f;
//        }
        
//        float getDelta()
//        {
//            return m_delta;
//        }
//        
//        void setDelta(float delta)
//        {
//            m_delta = delta;
//        }


        void sleep(int milliseconds)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        }
	};
}