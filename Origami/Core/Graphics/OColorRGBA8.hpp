//
//  OColorRGBA8.h
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 1/18/16.
//
//

#pragma once
#include <Core/OMacros.hpp>
#include <Core/OTypes.hpp>
#include <Core/Maths/OMaths.hpp>

NS_O_BEGIN

enum ColorEnums {
    R = 0,
    G,
    B,
    A
};

class OColorRGBA8
{
private:
    maths::vec4 m_Color;
    
public:
    OColorRGBA8() {
        m_Color = maths::vec4(1, 1, 1, 1);
    }
    OColorRGBA8(maths::vec4 &color) {
        m_Color = color;
    }
    OColorRGBA8(double red, double green, double blue, double alpha = 1)
    {
        m_Color[R] = red;
        m_Color[G] = green;
        m_Color[B] = blue;
        m_Color[A] = alpha;
    }
    ~OColorRGBA8() {}
    
public:
    float red()     { return m_Color[R]; };
    float green()   { return m_Color[G]; };
    float blue()    { return m_Color[B]; };
    float alpha()   { return m_Color[A]; };
    
public:
    void setRed(float red)      { m_Color[R] = red; }
    void setGreen(float green)  { m_Color[G] = green; }
    void setBlue(float blue)    { m_Color[B] = blue; }
    void setAlpha(float alpha)  { m_Color[A] = alpha; }
    void setColor(float red, float green, float blue, float alpha)
    {
        m_Color[R] = red;
        m_Color[G] = green;
        m_Color[B] = blue;
        m_Color[A] = alpha;
    }
    
public:
    maths::vec4 getColor(){ return m_Color; }
    uint getColorUint(){
        uint r = (uint)(m_Color.x * 255.0f);
        uint g = (uint)(m_Color.y * 255.0f);
        uint b = (uint)(m_Color.z * 255.0f);
        uint a = (uint)(m_Color.w * 255.0f);
        
        uint c = a << 24 | b << 16 | g << 8 | r;
        return c;
    }
    
public:  /// overloaded operators
    inline OColorRGBA8& operator=(const OColorRGBA8& color)
    {
        m_Color[R] = color.m_Color[R];
        m_Color[G] = color.m_Color[G];
        m_Color[B] = color.m_Color[B];
        m_Color[A] = color.m_Color[A];
        return *this;
    }
    
    inline OColorRGBA8& operator=(const maths::vec4& color)
    {
        m_Color[R] = color[R];
        m_Color[G] = color[G];
        m_Color[B] = color[B];
        m_Color[A] = color[A];
        return *this;
    }

    inline float& operator[](const unsigned index)         { return m_Color[index]; }
    inline float operator[](const unsigned index) const    { return m_Color[index]; }
    inline float& operator()(const unsigned index)         { return m_Color[index]; }
    inline float operator()(const unsigned index) const    { return m_Color[index]; }
    
};

NS_O_END