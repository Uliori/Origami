#pragma once

//#ifdef O_TARGET_DESKTOP
#include <chrono>
#include <thread>

#include <Core/OMacros.h>

NS_O_BEGIN
class OTimer
{
private:
    typedef std::chrono::system_clock		clock;
    typedef std::chrono::milliseconds  	milliseconds_type;

    std::chrono::time_point<clock>      m_Passed;

    std::chrono::time_point<clock>      m_PausedTime;

    double m_Time;
public:

    OTimer()
    {
        m_Time = 0;
        reset();
    }

    void reset()
    {
        m_Passed = clock::now();
    }

    double elapsed()
    {
        auto dif = std::chrono::duration_cast<milliseconds_type>(clock::now() - m_Passed);
        m_Passed = clock::now();

        m_Time += dif.count();

        return m_Time;
    }

    double getTime()
    {
        elapsed();
        return m_Time;
    }

    double getHours()
    {
        time_t tt = clock::to_time_t(clock::now());
        tm local_tm = *localtime(&tt);
        return local_tm.tm_hour;
        
    }
    
    double getMinutes()
    {
        time_t tt = clock::to_time_t(clock::now());
        tm local_tm = *localtime(&tt);
        return local_tm.tm_min;
    }
    
    double getDayMinutesTime()
    {
        time_t tt = clock::to_time_t(clock::now());
        tm local_tm = *localtime(&tt);
        return ((local_tm.tm_hour * 60) + local_tm.tm_min);
    }

    static void sleep(int milliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

};
NS_O_END
