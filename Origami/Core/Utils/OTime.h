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
    typedef std::chrono::milliseconds  		milliseconds_type;

    std::chrono::time_point<clock>          m_Passed;
    
    std::chrono::time_point<clock>          m_PausedTime;
    
    double m_time;
public:

    OTimer()
    {
        m_time = 0;
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
        
        m_time += dif.count();
        
        return m_time;
    }
    
    double getTime()
    {
        elapsed();
        return m_time;
    }

    double getMachineTime()
    {
        return std::chrono::duration_cast<milliseconds_type>(clock::now().time_since_epoch()).count();
    }

    static void sleep(int milliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
    
    
};
NS_O_END

