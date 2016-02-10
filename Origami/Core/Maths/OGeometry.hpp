#pragma once

#include "OMaths.hpp"

#include <Core/OMacros.hpp>

NS_O_BEGIN

using namespace maths;

class OSize
{
public:
    float width;
    float height;
public:

    operator vec2() const
    {
        return vec2(width, height);
    }

public:

    OSize();
    OSize(float width, float height);
    OSize(const OSize& other);
    explicit OSize(const vec2& point);

    OSize& operator= (const OSize& other);
    OSize& operator= (const vec2& point);
    OSize operator+(const OSize& right) const;
    OSize operator-(const OSize& right) const;
    OSize operator*(float a) const;
    OSize operator/(float a) const;

    void setSize(float width, float height);
    bool equals(const OSize& target) const;

    static const OSize ZERO;
};

/**Rectangle area.*/
class Rect
{
public:
    /**Low left point of rect.*/
    vec2 origin;
    /**Width and height of the rect.*/
    OSize  size;

public:

    Rect();
    Rect(float x, float y, float width, float height);
    Rect(const vec2& pos, const OSize& dimension);
    Rect(const Rect& other);

    Rect& operator= (const Rect& other);

    void setRect(float x, float y, float width, float height);
    float getMinX() const; /// return the leftmost x-value of current rect
    float getMidX() const; /// return the midpoint x-value of current rect
    float getMaxX() const; /// return the rightmost x-value of current rect
    float getMinY() const; /// return the bottommost y-value of current rect
    float getMidY() const; /// return the midpoint y-value of current rect
    float getMaxY() const; /// return the topmost y-value of current rect

    bool equals(const Rect& rect) const;
    bool containsPoint(const vec2& point) const;
    bool intersectsRect(const Rect& rect) const;
    bool intersectsCircle(const vec2& center, float radius) const;
    Rect unionWithRect(const Rect & rect) const;

    void merge(const Rect& rect);
    static const Rect ZERO;
};

NS_O_END
