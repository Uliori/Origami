/* mathlib
 *
 * Copyright (C) 2003-2004, Alexander Zaprjagaev <frustum@frustum.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#pragma once

#include <math.h>
#include <cstdlib>
#include <iostream>

#include <Core/OMacros.hpp>

NS_O_BEGIN
namespace maths {

#define EPSILON 1e-6f
#define DEG2RAD  0.0174532925f
#define RAD2DEG 57.29577951f
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_E                      2.71828182845904523536f
#define MATH_LOG10E                 0.4342944819032518f
#define MATH_LOG2E                  1.442695040888963387f
#define MATH_PI                     3.14159265358979323846f
#define MATH_PIOVER2                1.57079632679489661923f
#define MATH_PIOVER4                0.785398163397448309616f
#define MATH_PIX2                   6.28318530717958647693f
#define MATH_CLAMP(x, lo, hi)       ((x < lo) ? lo : ((x > hi) ? hi : x))
#ifndef M_1_PI
    #define M_1_PI                      0.31830988618379067154
#endif
    
#define ZERO_MEM(a) memset(a, 0, sizeof(a))
    
#define percent(A,B)((A * (B/100.0)))
#define addPercent(A,B)(A + (A * (B/100.0)))
    
    inline double fRand(double fMin, double fMax)
    {
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

struct vec2;
struct vec3;
struct vec4;
struct mat3;
struct mat4;
struct quat;

    inline float rsqrt(const float &x) {
        float length = sqrt(x);
        if (length < EPSILON) return 1.0f;
        return 1.0f / length;
    }
    
    inline float angle(float cx, float cy, float ex, float ey) {
        float dy = ey - cy;
        float dx = ex - cx;
        float theta = atan2(dy, dx); // range (-PI, PI]
        //if (theta < 0) theta = 360 + theta; // range [0, 360)
        return theta;
    }
/*****************************************************************************/
/*                                                                           */
/* vec2                                                                      */
/*                                                                           */
/*****************************************************************************/

struct vec2 {
    
    inline vec2() : x(0), y(0) { }
    inline vec2(float x,float y) : x(x), y(y) { }
    inline vec2(const float *v) : x(v[0]), y(v[1]) { }
    inline vec2(const vec2 &v) : x(v.x), y(v.y) { }
    
    inline int operator==(const vec2 &v) { return (fabs(x - v.x) < EPSILON && fabs(y - v.y) < EPSILON); }
    inline int operator!=(const vec2 &v) { return !(*this == v); }
    
    inline const vec2 operator*(float f) const { return vec2(x * f,y * f); }
    inline const vec2 operator/(float f) const { return vec2(x / f,y / f); }
    inline const vec2 operator+(const vec2 &v) const { return vec2(x + v.x,y + v.y); }
    inline const vec2 operator-() const { return vec2(-x,-y); }
    inline const vec2 operator-(const vec2 &v) const { return vec2(x - v.x,y - v.y); }
    
    inline vec2 &operator*=(float f) { return *this = *this * f; }
    inline vec2 &operator/=(float f) { return *this = *this / f; }
    inline vec2 &operator+=(const vec2 &v) { return *this = *this + v; }
    inline vec2 &operator-=(const vec2 &v) { return *this = *this - v; }
    
    inline float operator*(const vec2 &v) const { return x * v.x + y * v.y; }
    
    inline operator float*() { return (float*)&x; }
    inline operator const float*() const { return (float*)&x; }
    
    inline float &operator[](int i) { return ((float*)&x)[i]; }
    inline const float operator[](int i) const { return ((float*)&x)[i]; }
    
    inline float length() const { return sqrt(x * x + y * y); }
    inline void normalize() {
        float inv = rsqrt(x * x + y * y);
        x *= inv;
        y *= inv;
    }
    
    inline void saturate() {
        if (x < 0.0f) x = 0.0f;
        else if (x > 1.0f) x = 1.0f;
        if (y < 0.0f) y = 0.0f;
        else if (y > 1.0f) y = 1.0f;
    }
    
    inline void clamp(const vec2 &min, const vec2 &max) {
        if (x < min.x) x = min.x;
        else if (x > max.x) x = max.x;
        if (y < min.y) y = min.y;
        else if (y > max.y) y = max.y;
    }
    
    inline friend std::ostream& operator<<(std::ostream& stream, const vec2& vector)
    {
        stream << "vec2: (" << vector.x << ", " << vector.y << ")";
        return stream;
    }
    
    union {
        struct {
            float x,y;
        };
        float v[2];
    };
};

/*****************************************************************************/
/*                                                                           */
/* vec3                                                                      */
/*                                                                           */
/*****************************************************************************/

struct vec3 {
    
    inline vec3() : x(0), y(0), z(0) { }
    inline vec3(float x,float y,float z) : x(x), y(y), z(z) { }
    inline vec3(const float *v) : x(v[0]), y(v[1]), z(v[2]) { }
    inline vec3(const vec3 &v) : x(v.x), y(v.y), z(v.z) { }
    inline vec3(const vec4 &v);
    
    inline int operator==(const vec3 &v) { return (fabs(x - v.x) < EPSILON && fabs(y - v.y) < EPSILON && fabs(z - v.z) < EPSILON); }
    inline int operator!=(const vec3 &v) { return !(*this == v); }
    
    inline const vec3 operator*(float f) const { return vec3(x * f,y * f,z * f); }
    inline const vec3 operator/(float f) const { return vec3(x / f,y / f,z / f); }
    inline const vec3 operator+(const vec3 &v) const { return vec3(x + v.x,y + v.y,z + v.z); }
    inline const vec3 operator-() const { return vec3(-x,-y,-z); }
    inline const vec3 operator-(const vec3 &v) const { return vec3(x - v.x,y - v.y,z - v.z); }
    
    inline vec3 &operator*=(float f) { return *this = *this * f; }
    inline vec3 &operator/=(float f) { return *this = *this / f; }
    inline vec3 &operator+=(const vec3 &v) { return *this = *this + v; }
    inline vec3 &operator-=(const vec3 &v) { return *this = *this - v; }
    
    inline float operator*(const vec3 &v) const { return x * v.x + y * v.y + z * v.z; }
    inline float operator*(const vec4 &v) const;
    
    inline operator float*() { return (float*)&x; }
    inline operator const float*() const { return (float*)&x; }
    
    inline float &operator[](int i) { return ((float*)&x)[i]; }
    inline const float operator[](int i) const { return ((float*)&x)[i]; }
    
    inline float length() const { return sqrt(x * x + y * y + z * z); }
    inline void normalize() {
        float inv = rsqrt(x * x + y * y + z * z);
        x *= inv;
        y *= inv;
        z *= inv;
    }
    
    inline void cross(const vec3 &v1, const vec3 &v2) {
        x = v1.y * v2.z - v1.z * v2.y;
        y = v1.z * v2.x - v1.x * v2.z;
        z = v1.x * v2.y - v1.y * v2.x;
    }
    
    inline void saturate() {
        if (x < 0.0f) x = 0.0f;
        else if (x > 1.0f) x = 1.0f;
        if (y < 0.0f) y = 0.0f;
        else if (y > 1.0f) y = 1.0f;
        if (z < 0.0f) z = 0.0f;
        else if (z > 1.0f) z = 1.0f;
    }
    
    inline void clamp(const vec3 &min, const vec3 &max) {
        if (x < min.x) x = min.x;
        else if (x > max.x) x = max.x;
        if (y < min.y) y = min.y;
        else if (y > max.y) y = max.y;
        if (z < min.z) z = min.z;
        else if (z > max.z) z = max.z;
    }
    
    inline friend std::ostream& operator<<(std::ostream& stream, const vec3& vector)
    {
        stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
        return stream;
    }
    
    union {
        struct {
            float x,y,z;
        };
        float v[3];
    };
};

    inline float length(const vec3 &v) {
        return v.length();
    }
    
    inline vec3 normalize(const vec3 &v) {
        vec3 ret = v;
        ret.normalize();
        return ret;
    }
    
    inline vec3 cross(const vec3 &v1, const vec3 &v2) {
        vec3 ret;
        ret.x = v1.y * v2.z - v1.z * v2.y;
        ret.y = v1.z * v2.x - v1.x * v2.z;
        ret.z = v1.x * v2.y - v1.y * v2.x;
        return ret;
    }
    
    inline vec3 saturate(const vec3 &v) {
        vec3 ret = v;
        ret.saturate();
        return ret;
    }
    
    inline vec3 clamp(const vec3 &v, const vec3 &min, const vec3 &max) {
        vec3 ret = v;
        ret.clamp(min, max);
        return ret;
    }

/*****************************************************************************/
/*                                                                           */
/* vec4                                                                      */
/*                                                                           */
/*****************************************************************************/

struct vec4 {
    
    inline vec4() : x(0), y(0), z(0), w(1) { }
    inline vec4(float x,float y,float z,float w) : x(x), y(y), z(z), w(w) { }
    inline vec4(const float *v) : x(v[0]), y(v[1]), z(v[2]), w(v[3]) { }
    inline vec4(const vec3 &v) : x(v.x), y(v.y), z(v.z), w(1) { }
    inline vec4(const vec3 &v,float w) : x(v.x), y(v.y), z(v.z), w(w) { }
    inline vec4(const vec4 &v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
    
    inline int operator==(const vec4 &v) { return (fabs(x - v.x) < EPSILON && fabs(y - v.y) < EPSILON && fabs(z - v.z) < EPSILON && fabs(w - v.w) < EPSILON); }
    inline int operator!=(const vec4 &v) { return !(*this == v); }
    
    inline const vec4 operator*(float f) const { return vec4(x * f,y * f,z * f,w * f); }
    inline const vec4 operator/(float f) const { return vec4(x / f,y / f,z / f,w / f); }
    inline const vec4 operator+(const vec4 &v) const { return vec4(x + v.x,y + v.y,z + v.z,w + v.w); }
    inline const vec4 operator-() const { return vec4(-x,-y,-z,-w); }
    inline const vec4 operator-(const vec4 &v) const { return vec4(x - v.x,y - v.y,z - v.z,z - v.w); }
    
    inline vec4 &operator*=(float f) { return *this = *this * f; }
    inline vec4 &operator/=(float f) { return *this = *this / f; }
    inline vec4 &operator+=(const vec4 &v) { return *this = *this + v; }
    inline vec4 &operator-=(const vec4 &v) { return *this = *this - v; }
    
    inline float operator*(const vec3 &v) const { return x * v.x + y * v.y + z * v.z + w; }
    inline float operator*(const vec4 &v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }
    
    inline operator float*() { return (float*)&x; }
    inline operator const float*() const { return (float*)&x; }
    
    inline float &operator[](int i) { return ((float*)&x)[i]; }
    inline const float operator[](int i) const { return ((float*)&x)[i]; }
    
    inline float length() const { return sqrt(x * x + y * y + z * z + w * w); }
    inline void normalize() {
        float inv = rsqrt(x * x + y * y + z * z + w * w);
        x *= inv;
        y *= inv;
        z *= inv;
        w *= inv;
    }
    
    inline void saturate() {
        if (x < 0.0f) x = 0.0f;
        else if (x > 1.0f) x = 1.0f;
        if (y < 0.0f) y = 0.0f;
        else if (y > 1.0f) y = 1.0f;
        if (z < 0.0f) z = 0.0f;
        else if (z > 1.0f) z = 1.0f;
        if (w < 0.0f) w = 0.0f;
        else if (w > 1.0f) w = 1.0f;
    }
    
    inline void clamp(const vec4 &min, const vec4 &max) {
        if (x < min.x) x = min.x;
        else if (x > max.x) x = max.x;
        if (y < min.y) y = min.y;
        else if (y > max.y) y = max.y;
        if (z < min.z) z = min.z;
        else if (z > max.z) z = max.z;
        if (w < min.w) w = min.w;
        else if (w > max.w) w = max.w;
    }
    
    inline friend std::ostream& operator<<(std::ostream& stream, const vec4& vector)
    {
        stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
        return stream;
    }
    
    union {
        struct {
            float x,y,z,w;
        };
        float v[4];
    };
};

    inline vec3::vec3(const vec4 &v) : x(v.x), y(v.y), z(v.z) { }
    
    inline float vec3::operator*(const vec4 &v) const {
        return x * v.x + y * v.y + z * v.z + v.w;
    }
    
    inline float dot(const vec2 &v1, const vec2 &v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }
    
    inline float dot(const vec3 &v1, const vec3 &v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }
    
    inline float dot(const vec3 &v1, const vec4 &v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v2.w;
    }
    
    inline float dot(const vec4 &v1, const vec3 &v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w;
    }
    
    inline float dot(const vec4 &v1, const vec4 &v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }
    
    inline float length(const vec4 &v) {
        return v.length();
    }
    
    inline vec4 normalize(const vec4 &v) {
        vec4 ret = v;
        ret.normalize();
        return ret;
    }
    
    inline vec4 saturate(const vec4 &v) {
        vec4 ret = v;
        ret.saturate();
        return ret;
    }
    
    inline vec4 clamp(const vec4 &v, const vec4 &min, const vec4 &max) {
        vec4 ret = v;
        ret.clamp(min, max);
        return ret;
    }

/*****************************************************************************/
/*                                                                           */
/* mat3                                                                      */
/*                                                                           */
/*****************************************************************************/

struct mat3 {
    
    mat3() {
        mat[0] = 1.0; mat[3] = 0.0; mat[6] = 0.0;
        mat[1] = 0.0; mat[4] = 1.0; mat[7] = 0.0;
        mat[2] = 0.0; mat[5] = 0.0; mat[8] = 1.0;
    }
    mat3(const float *m) {
        mat[0] = m[0]; mat[3] = m[3]; mat[6] = m[6];
        mat[1] = m[1]; mat[4] = m[4]; mat[7] = m[7];
        mat[2] = m[2]; mat[5] = m[5]; mat[8] = m[8];
    }
    mat3(const mat3 &m) {
        mat[0] = m[0]; mat[3] = m[3]; mat[6] = m[6];
        mat[1] = m[1]; mat[4] = m[4]; mat[7] = m[7];
        mat[2] = m[2]; mat[5] = m[5]; mat[8] = m[8];
    }
    mat3(const mat4 &m);
    explicit mat3(const quat &q);
    
    vec3 operator*(const vec3 &v) const {
        vec3 ret;
        ret[0] = mat[0] * v[0] + mat[3] * v[1] + mat[6] * v[2];
        ret[1] = mat[1] * v[0] + mat[4] * v[1] + mat[7] * v[2];
        ret[2] = mat[2] * v[0] + mat[5] * v[1] + mat[8] * v[2];
        return ret;
    }
    vec4 operator*(const vec4 &v) const {
        vec4 ret;
        ret[0] = mat[0] * v[0] + mat[3] * v[1] + mat[6] * v[2];
        ret[1] = mat[1] * v[0] + mat[4] * v[1] + mat[7] * v[2];
        ret[2] = mat[2] * v[0] + mat[5] * v[1] + mat[8] * v[2];
        ret[3] = v[3];
        return ret;
    }
    mat3 operator*(float f) const {
        mat3 ret;
        ret[0] = mat[0] * f; ret[3] = mat[3] * f; ret[6] = mat[6] * f;
        ret[1] = mat[1] * f; ret[4] = mat[4] * f; ret[7] = mat[7] * f;
        ret[2] = mat[2] * f; ret[5] = mat[5] * f; ret[8] = mat[8] * f;
        return ret;
    }
    mat3 operator*(const mat3 &m) const {
        mat3 ret;
        ret[0] = mat[0] * m[0] + mat[3] * m[1] + mat[6] * m[2];
        ret[1] = mat[1] * m[0] + mat[4] * m[1] + mat[7] * m[2];
        ret[2] = mat[2] * m[0] + mat[5] * m[1] + mat[8] * m[2];
        ret[3] = mat[0] * m[3] + mat[3] * m[4] + mat[6] * m[5];
        ret[4] = mat[1] * m[3] + mat[4] * m[4] + mat[7] * m[5];
        ret[5] = mat[2] * m[3] + mat[5] * m[4] + mat[8] * m[5];
        ret[6] = mat[0] * m[6] + mat[3] * m[7] + mat[6] * m[8];
        ret[7] = mat[1] * m[6] + mat[4] * m[7] + mat[7] * m[8];
        ret[8] = mat[2] * m[6] + mat[5] * m[7] + mat[8] * m[8];
        return ret;
    }
    mat3 operator+(const mat3 &m) const {
        mat3 ret;
        ret[0] = mat[0] + m[0]; ret[3] = mat[3] + m[3]; ret[6] = mat[6] + m[6];
        ret[1] = mat[1] + m[1]; ret[4] = mat[4] + m[4]; ret[7] = mat[7] + m[7];
        ret[2] = mat[2] + m[2]; ret[5] = mat[5] + m[5]; ret[8] = mat[8] + m[8];
        return ret;
    }
    mat3 operator-(const mat3 &m) const {
        mat3 ret;
        ret[0] = mat[0] - m[0]; ret[3] = mat[3] - m[3]; ret[6] = mat[6] - m[6];
        ret[1] = mat[1] - m[1]; ret[4] = mat[4] - m[4]; ret[7] = mat[7] - m[7];
        ret[2] = mat[2] - m[2]; ret[5] = mat[5] - m[5]; ret[8] = mat[8] - m[8];
        return ret;
    }
    
    mat3 &operator*=(float f) { return *this = *this * f; }
    mat3 &operator*=(const mat3 &m) { return *this = *this * m; }
    mat3 &operator+=(const mat3 &m) { return *this = *this + m; }
    mat3 &operator-=(const mat3 &m) { return *this = *this - m; }
    
    operator float*() { return mat; }
    operator const float*() const { return mat; }
    
    float &operator[](int i) { return mat[i]; }
    const float operator[](int i) const { return mat[i]; }
    
    mat3 transpose() const {
        mat3 ret;
        ret[0] = mat[0]; ret[3] = mat[1]; ret[6] = mat[2];
        ret[1] = mat[3]; ret[4] = mat[4]; ret[7] = mat[5];
        ret[2] = mat[6]; ret[5] = mat[7]; ret[8] = mat[8];
        return ret;
    }
    float determinant() const {
        float det;
        det = mat[0] * (mat[4] * mat[8] - mat[7] * mat[5]);
        det -= mat[3] * (mat[1] * mat[8] - mat[7] * mat[2]);
        det += mat[6] * (mat[1] * mat[5] - mat[4] * mat[2]);
        return det;
    }
    mat3 inverse() const {
        mat3 ret;
        float det = determinant();
        if (det < EPSILON) return ret;
        float idet = 1.0f / det;
        ret[0] = (mat[4] * mat[8] - mat[7] * mat[5]) * idet;
        ret[1] = -(mat[1] * mat[8] - mat[7] * mat[2]) * idet;
        ret[2] = (mat[1] * mat[5] - mat[4] * mat[2]) * idet;
        ret[3] = -(mat[3] * mat[8] - mat[6] * mat[5]) * idet;
        ret[4] = (mat[0] * mat[8] - mat[6] * mat[2]) * idet;
        ret[5] = -(mat[0] * mat[5] - mat[3] * mat[2]) * idet;
        ret[6] = (mat[3] * mat[7] - mat[6] * mat[4]) * idet;
        ret[7] = -(mat[0] * mat[7] - mat[6] * mat[1]) * idet;
        ret[8] = (mat[0] * mat[4] - mat[3] * mat[1]) * idet;
        return ret;
    }
    mat3 orthonormalize() const {
        mat3 ret;
        vec3 x(mat[0], mat[1], mat[2]);
        vec3 y(mat[3], mat[4], mat[5]);
        vec3 z;
        x.normalize();
        z.cross(x, y);
        z.normalize();
        y.cross(z, x);
        y.normalize();
        ret[0] = x.x; ret[3] = y.x; ret[6] = z.x;
        ret[1] = x.y; ret[4] = y.y; ret[7] = z.y;
        ret[2] = x.z; ret[5] = y.z; ret[8] = z.z;
        return ret;
    }
    
    void zero() {
        mat[0] = 0.0; mat[3] = 0.0; mat[6] = 0.0;
        mat[1] = 0.0; mat[4] = 0.0; mat[7] = 0.0;
        mat[2] = 0.0; mat[5] = 0.0; mat[8] = 0.0;
    }
    void identity() {
        mat[0] = 1.0; mat[3] = 0.0; mat[6] = 0.0;
        mat[1] = 0.0; mat[4] = 1.0; mat[7] = 0.0;
        mat[2] = 0.0; mat[5] = 0.0; mat[8] = 1.0;
    }
    
    void rotate(const vec3 &axis, float angle) {
        float rad = angle * DEG2RAD;
        float c = cos(rad);
        float s = sin(rad);
        vec3 v = axis;
        v.normalize();
        float xx = v.x * v.x;
        float yy = v.y * v.y;
        float zz = v.z * v.z;
        float xy = v.x * v.y;
        float yz = v.y * v.z;
        float zx = v.z * v.x;
        float xs = v.x * s;
        float ys = v.y * s;
        float zs = v.z * s;
        mat[0] = (1.0f - c) * xx + c; mat[3] = (1.0f - c) * xy - zs; mat[6] = (1.0f - c) * zx + ys;
        mat[1] = (1.0f - c) * xy + zs; mat[4] = (1.0f - c) * yy + c; mat[7] = (1.0f - c) * yz - xs;
        mat[2] = (1.0f - c) * zx - ys; mat[5] = (1.0f - c) * yz + xs; mat[8] = (1.0f - c) * zz + c;
    }
    void rotate(float x, float y, float z, float angle) {
        rotate(vec3(x, y, z), angle);
    }
    void rotateX(float angle) {
        float rad = angle * DEG2RAD;
        float c = cos(rad);
        float s = sin(rad);
        mat[0] = 1.0; mat[3] = 0.0; mat[6] = 0.0;
        mat[1] = 0.0; mat[4] = c; mat[7] = -s;
        mat[2] = 0.0; mat[5] = s; mat[8] = c;
    }
    void rotateY(float angle) {
        float rad = angle * DEG2RAD;
        float c = cos(rad);
        float s = sin(rad);
        mat[0] = c; mat[3] = 0.0; mat[6] = s;
        mat[1] = 0.0; mat[4] = 1.0; mat[7] = 0.0;
        mat[2] = -s; mat[5] = 0.0; mat[8] = c;
    }
    void rotateZ(float angle) {
        float rad = angle * DEG2RAD;
        float c = cos(rad);
        float s = sin(rad);
        mat[0] = c; mat[3] = -s; mat[6] = 0.0;
        mat[1] = s; mat[4] = c; mat[7] = 0.0;
        mat[2] = 0.0; mat[5] = 0.0; mat[8] = 1.0;
    }
    void scale(const vec3 &v) {
        mat[0] = v.x; mat[3] = 0.0; mat[6] = 0.0;
        mat[1] = 0.0; mat[4] = v.y; mat[7] = 0.0;
        mat[2] = 0.0; mat[5] = 0.0; mat[8] = v.z;
    }
    void scale(float x, float y, float z) {
        scale(vec3(x, y, z));
    }
    
    union {
        struct {
            float m00, m10, m20;
            float m01, m11, m21;
            float m02, m12, m22;
        };
        float mat[9];
    };
};

    inline mat3 transpose(const mat3 &m) {
        return m.transpose();
    }
    
    inline mat3 inverse(const mat3 &m) {
        return m.inverse();
    }
    
    inline mat3 orthonormalize(const mat3 &m) {
        return m.orthonormalize();
    }

/*****************************************************************************/
/*                                                                           */
/* mat4                                                                      */
/*                                                                           */
/*****************************************************************************/

struct mat4 {
    
    mat4() {
        mat[0] = 1.0; mat[4] = 0.0; mat[8] = 0.0; mat[12] = 0.0;
        mat[1] = 0.0; mat[5] = 1.0; mat[9] = 0.0; mat[13] = 0.0;
        mat[2] = 0.0; mat[6] = 0.0; mat[10] = 1.0; mat[14] = 0.0;
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
    }
    mat4(const vec3 &v) {
        translate(v);
    }
    mat4(float x,float y,float z) {
        translate(x,y,z);
    }
    mat4(const vec3 &axis,float angle) {
        rotate(axis,angle);
    }
    mat4(float x,float y,float z,float angle) {
        rotate(x,y,z,angle);
    }
    
    explicit mat4(const quat &q);
    mat4(const mat3 &m) {
        mat[0] = m[0]; mat[4] = m[3]; mat[8] = m[6]; mat[12] = 0.0;
        mat[1] = m[1]; mat[5] = m[4]; mat[9] = m[7]; mat[13] = 0.0;
        mat[2] = m[2]; mat[6] = m[5]; mat[10] = m[8]; mat[14] = 0.0;
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
    }
    mat4(const float *m) {
        mat[0] = m[0]; mat[4] = m[4]; mat[8] = m[8]; mat[12] = m[12];
        mat[1] = m[1]; mat[5] = m[5]; mat[9] = m[9]; mat[13] = m[13];
        mat[2] = m[2]; mat[6] = m[6]; mat[10] = m[10]; mat[14] = m[14];
        mat[3] = m[3]; mat[7] = m[7]; mat[11] = m[11]; mat[15] = m[15];
    }
    mat4(const mat4 &m) {
        mat[0] = m[0]; mat[4] = m[4]; mat[8] = m[8]; mat[12] = m[12];
        mat[1] = m[1]; mat[5] = m[5]; mat[9] = m[9]; mat[13] = m[13];
        mat[2] = m[2]; mat[6] = m[6]; mat[10] = m[10]; mat[14] = m[14];
        mat[3] = m[3]; mat[7] = m[7]; mat[11] = m[11]; mat[15] = m[15];
    }
    
    int operator==(const mat4 &m) const {
        return fabs(mat[0] - m.mat[0]) < EPSILON && fabs(mat[1] - m.mat[1]) < EPSILON && fabs(mat[2] - m.mat[2]) < EPSILON && fabs(mat[3] - m.mat[3]) < EPSILON &&
        fabs(mat[4] - m.mat[4]) < EPSILON && fabs(mat[5] - m.mat[5]) < EPSILON && fabs(mat[6] - m.mat[6]) < EPSILON && fabs(mat[7] - m.mat[7]) < EPSILON &&
        fabs(mat[8] - m.mat[8]) < EPSILON && fabs(mat[9] - m.mat[9]) < EPSILON && fabs(mat[10] - m.mat[10]) < EPSILON && fabs(mat[11] - m.mat[11]) < EPSILON &&
        fabs(mat[12] - m.mat[12]) < EPSILON && fabs(mat[13] - m.mat[13]) < EPSILON && fabs(mat[14] - m.mat[14]) < EPSILON && fabs(mat[15] - m.mat[15]) < EPSILON;
    }
    int operator!=(const mat4 &m) const { return !(*this == m); }
    
    vec3 operator*(const vec3 &v) const {
        vec3 ret;
        ret[0] = mat[0] * v[0] + mat[4] * v[1] + mat[8] * v[2] + mat[12];
        ret[1] = mat[1] * v[0] + mat[5] * v[1] + mat[9] * v[2] + mat[13];
        ret[2] = mat[2] * v[0] + mat[6] * v[1] + mat[10] * v[2] + mat[14];
        return ret;
    }
    vec4 operator*(const vec4 &v) const {
        vec4 ret;
        ret[0] = mat[0] * v[0] + mat[4] * v[1] + mat[8] * v[2] + mat[12] * v[3];
        ret[1] = mat[1] * v[0] + mat[5] * v[1] + mat[9] * v[2] + mat[13] * v[3];
        ret[2] = mat[2] * v[0] + mat[6] * v[1] + mat[10] * v[2] + mat[14] * v[3];
        ret[3] = mat[3] * v[0] + mat[7] * v[1] + mat[11] * v[2] + mat[15] * v[3];
        return ret;
    }
    mat4 operator*(float f) const {
        mat4 ret;
        ret[0] = mat[0] * f; ret[4] = mat[4] * f; ret[8] = mat[8] * f; ret[12] = mat[12] * f;
        ret[1] = mat[1] * f; ret[5] = mat[5] * f; ret[9] = mat[9] * f; ret[13] = mat[13] * f;
        ret[2] = mat[2] * f; ret[6] = mat[6] * f; ret[10] = mat[10] * f; ret[14] = mat[14] * f;
        ret[3] = mat[3] * f; ret[7] = mat[7] * f; ret[11] = mat[11] * f; ret[15] = mat[15] * f;
        return ret;
    }
    mat4 operator*(const mat4 &m) const {
        mat4 ret;
        ret[0] = mat[0] * m[0] + mat[4] * m[1] + mat[8] * m[2] + mat[12] * m[3];
        ret[1] = mat[1] * m[0] + mat[5] * m[1] + mat[9] * m[2] + mat[13] * m[3];
        ret[2] = mat[2] * m[0] + mat[6] * m[1] + mat[10] * m[2] + mat[14] * m[3];
        ret[3] = mat[3] * m[0] + mat[7] * m[1] + mat[11] * m[2] + mat[15] * m[3];
        ret[4] = mat[0] * m[4] + mat[4] * m[5] + mat[8] * m[6] + mat[12] * m[7];
        ret[5] = mat[1] * m[4] + mat[5] * m[5] + mat[9] * m[6] + mat[13] * m[7];
        ret[6] = mat[2] * m[4] + mat[6] * m[5] + mat[10] * m[6] + mat[14] * m[7];
        ret[7] = mat[3] * m[4] + mat[7] * m[5] + mat[11] * m[6] + mat[15] * m[7];
        ret[8] = mat[0] * m[8] + mat[4] * m[9] + mat[8] * m[10] + mat[12] * m[11];
        ret[9] = mat[1] * m[8] + mat[5] * m[9] + mat[9] * m[10] + mat[13] * m[11];
        ret[10] = mat[2] * m[8] + mat[6] * m[9] + mat[10] * m[10] + mat[14] * m[11];
        ret[11] = mat[3] * m[8] + mat[7] * m[9] + mat[11] * m[10] + mat[15] * m[11];
        ret[12] = mat[0] * m[12] + mat[4] * m[13] + mat[8] * m[14] + mat[12] * m[15];
        ret[13] = mat[1] * m[12] + mat[5] * m[13] + mat[9] * m[14] + mat[13] * m[15];
        ret[14] = mat[2] * m[12] + mat[6] * m[13] + mat[10] * m[14] + mat[14] * m[15];
        ret[15] = mat[3] * m[12] + mat[7] * m[13] + mat[11] * m[14] + mat[15] * m[15];
        return ret;
    }
    mat4 operator+(const mat4 &m) const {
        mat4 ret;
        ret[0] = mat[0] + m[0]; ret[4] = mat[4] + m[4]; ret[8] = mat[8] + m[8]; ret[12] = mat[12] + m[12];
        ret[1] = mat[1] + m[1]; ret[5] = mat[5] + m[5]; ret[9] = mat[9] + m[9]; ret[13] = mat[13] + m[13];
        ret[2] = mat[2] + m[2]; ret[6] = mat[6] + m[6]; ret[10] = mat[10] + m[10]; ret[14] = mat[14] + m[14];
        ret[3] = mat[3] + m[3]; ret[7] = mat[7] + m[7]; ret[11] = mat[11] + m[11]; ret[15] = mat[15] + m[15];
        return ret;
    }
    mat4 operator-(const mat4 &m) const {
        mat4 ret;
        ret[0] = mat[0] - m[0]; ret[4] = mat[4] - m[4]; ret[8] = mat[8] - m[8]; ret[12] = mat[12] - m[12];
        ret[1] = mat[1] - m[1]; ret[5] = mat[5] - m[5]; ret[9] = mat[9] - m[9]; ret[13] = mat[13] - m[13];
        ret[2] = mat[2] - m[2]; ret[6] = mat[6] - m[6]; ret[10] = mat[10] - m[10]; ret[14] = mat[14] - m[14];
        ret[3] = mat[3] - m[3]; ret[7] = mat[7] - m[7]; ret[11] = mat[11] - m[11]; ret[15] = mat[15] - m[15];
        return ret;
    }
    
    mat4 &operator*=(float f) { return *this = *this * f; }
    mat4 &operator*=(const mat4 &m) { return *this = *this * m; }
    mat4 &operator+=(const mat4 &m) { return *this = *this + m; }
    mat4 &operator-=(const mat4 &m) { return *this = *this - m; }
    
    operator float*() { return mat; }
    operator const float*() const { return mat; }
    
    float &operator[](int i) { return mat[i]; }
    const float operator[](int i) const { return mat[i]; }
    
    inline vec4 row(int i) const { return vec4(mat[i + 0], mat[i + 4], mat[i + 8], mat[i + 12]); }
    inline void setRow(int i, const vec4 &v) { mat[i + 0] = v[0]; mat[i + 4] = v[1]; mat[i + 8] = v[2]; mat[i + 12] = v[3]; }
    
    inline vec4 col(int i) const { return vec4(mat[i * 4 + 0], mat[i * 4 + 1], mat[i * 4 + 2], mat[i * 4 + 3]); }
    inline void setCol(int i, const vec4 &v) { mat[i * 4 + 0] = v[0]; mat[i * 4 + 1] = v[1]; mat[i * 4 + 2] = v[2]; mat[i * 4 + 3] = v[3]; }
    
    inline int isIdentity() const {
        return fabs(mat[0] - 1.0f) < EPSILON && fabs(mat[4]) < EPSILON && fabs(mat[8]) < EPSILON && fabs(mat[12]) < EPSILON &&
        fabs(mat[1]) < EPSILON && fabs(mat[5] - 1.0f) < EPSILON && fabs(mat[9]) < EPSILON && fabs(mat[13]) < EPSILON &&
        fabs(mat[2]) < EPSILON && fabs(mat[6]) < EPSILON && fabs(mat[10] - 1.0f) < EPSILON && fabs(mat[14]) < EPSILON &&
        fabs(mat[3]) < EPSILON && fabs(mat[7]) < EPSILON && fabs(mat[11]) < EPSILON && fabs(mat[15] - 1.0f) < EPSILON;
    }
    
    mat4 rotation() const {
        mat4 ret;
        ret[0] = mat[0]; ret[4] = mat[4]; ret[8] = mat[8]; ret[12] = 0;
        ret[1] = mat[1]; ret[5] = mat[5]; ret[9] = mat[9]; ret[13] = 0;
        ret[2] = mat[2]; ret[6] = mat[6]; ret[10] = mat[10]; ret[14] = 0;
        ret[3] = 0; ret[7] = 0; ret[11] = 0; ret[15] = 1;
        return ret;
    }
    mat4 transpose() const {
        mat4 ret;
        ret[0] = mat[0]; ret[4] = mat[1]; ret[8] = mat[2]; ret[12] = mat[3];
        ret[1] = mat[4]; ret[5] = mat[5]; ret[9] = mat[6]; ret[13] = mat[7];
        ret[2] = mat[8]; ret[6] = mat[9]; ret[10] = mat[10]; ret[14] = mat[11];
        ret[3] = mat[12]; ret[7] = mat[13]; ret[11] = mat[14]; ret[15] = mat[15];
        return ret;
    }
    mat4 transposeRotation() const {
        mat4 ret;
        ret[0] = mat[0]; ret[4] = mat[1]; ret[8] = mat[2]; ret[12] = mat[12];
        ret[1] = mat[4]; ret[5] = mat[5]; ret[9] = mat[6]; ret[13] = mat[13];
        ret[2] = mat[8]; ret[6] = mat[9]; ret[10] = mat[10]; ret[14] = mat[14];
        ret[3] = mat[3]; ret[7] = mat[7]; ret[14] = mat[14]; ret[15] = mat[15];
        return ret;
    }
    
    float determinant() const {
        float det;
        det = mat[0] * (mat[5] * (mat[10] * mat[15] - mat[14] * mat[11]) - mat[9] * (mat[6] * mat[15] - mat[14] * mat[7]) + mat[13] * (mat[6] * mat[11] - mat[10] * mat[7]));
        det -= mat[4] * (mat[1] * (mat[10] * mat[15] - mat[14] * mat[11]) - mat[9] * (mat[2] * mat[15] - mat[14] * mat[3]) + mat[13] * (mat[2] * mat[11] - mat[10] * mat[3]));
        det += mat[8] * (mat[1] * (mat[6] * mat[15] - mat[14] * mat[7]) - mat[5] * (mat[2] * mat[15] - mat[14] * mat[3]) + mat[13] * (mat[2] * mat[7] - mat[6] * mat[3]));
        det -= mat[12] * (mat[1] * (mat[6] * mat[11] - mat[10] * mat[7]) - mat[5] * (mat[2] * mat[11] - mat[10] * mat[3]) + mat[9] * (mat[2] * mat[7] - mat[6] * mat[3]));
        return det;
    }
    
    mat4 inverse() const {
        mat4 ret;
        float det = determinant();
        if (det < EPSILON) return ret;
        float idet = 1.0f / det;
        ret[0] = (mat[5] * (mat[10] * mat[15] - mat[14] * mat[11]) - mat[9] * (mat[6] * mat[15] - mat[14] * mat[7]) + mat[13] * (mat[6] * mat[11] - mat[10] * mat[7])) * idet;
        ret[1] = -(mat[1] * (mat[10] * mat[15] - mat[14] * mat[11]) - mat[9] * (mat[2] * mat[15] - mat[14] * mat[3]) + mat[13] * (mat[2] * mat[11] - mat[10] * mat[3])) * idet;
        ret[2] = (mat[1] * (mat[6] * mat[15] - mat[14] * mat[7]) - mat[5] * (mat[2] * mat[15] - mat[14] * mat[3]) + mat[13] * (mat[2] * mat[7] - mat[6] * mat[3])) * idet;
        ret[3] = -(mat[1] * (mat[6] * mat[11] - mat[10] * mat[7]) - mat[5] * (mat[2] * mat[11] - mat[10] * mat[3]) + mat[9] * (mat[2] * mat[7] - mat[6] * mat[3])) * idet;
        ret[4] = -(mat[4] * (mat[10] * mat[15] - mat[14] * mat[11]) - mat[8] * (mat[6] * mat[15] - mat[14] * mat[7]) + mat[12] * (mat[6] * mat[11] - mat[10] * mat[7])) * idet;
        ret[5] = (mat[0] * (mat[10] * mat[15] - mat[14] * mat[11]) - mat[8] * (mat[2] * mat[15] - mat[14] * mat[3]) + mat[12] * (mat[2] * mat[11] - mat[10] * mat[3])) * idet;
        ret[6] = -(mat[0] * (mat[6] * mat[15] - mat[14] * mat[7]) - mat[4] * (mat[2] * mat[15] - mat[14] * mat[3]) + mat[12] * (mat[2] * mat[7] - mat[6] * mat[3])) * idet;
        ret[7] = (mat[0] * (mat[6] * mat[11] - mat[10] * mat[7]) - mat[4] * (mat[2] * mat[11] - mat[10] * mat[3]) + mat[8] * (mat[2] * mat[7] - mat[6] * mat[3])) * idet;
        ret[8] = (mat[4] * (mat[9] * mat[15] - mat[13] * mat[11]) - mat[8] * (mat[5] * mat[15] - mat[13] * mat[7]) + mat[12] * (mat[5] * mat[11] - mat[9] * mat[7])) * idet;
        ret[9] = -(mat[0] * (mat[9] * mat[15] - mat[13] * mat[11]) - mat[8] * (mat[1] * mat[15] - mat[13] * mat[3]) + mat[12] * (mat[1] * mat[11] - mat[9] * mat[3])) * idet;
        ret[10] = (mat[0] * (mat[5] * mat[15] - mat[13] * mat[7]) - mat[4] * (mat[1] * mat[15] - mat[13] * mat[3]) + mat[12] * (mat[1] * mat[7] - mat[5] * mat[3])) * idet;
        ret[11] = -(mat[0] * (mat[5] * mat[11] - mat[9] * mat[7]) - mat[4] * (mat[1] * mat[11] - mat[9] * mat[3]) + mat[8] * (mat[1] * mat[7] - mat[5] * mat[3])) * idet;
        ret[12] = -(mat[4] * (mat[9] * mat[14] - mat[13] * mat[10]) - mat[8] * (mat[5] * mat[14] - mat[13] * mat[6]) + mat[12] * (mat[5] * mat[10] - mat[9] * mat[6])) * idet;
        ret[13] = (mat[0] * (mat[9] * mat[14] - mat[13] * mat[10]) - mat[8] * (mat[1] * mat[14] - mat[13] * mat[2]) + mat[12] * (mat[1] * mat[10] - mat[9] * mat[2])) * idet;
        ret[14] = -(mat[0] * (mat[5] * mat[14] - mat[13] * mat[6]) - mat[4] * (mat[1] * mat[14] - mat[13] * mat[2]) + mat[12] * (mat[1] * mat[6] - mat[5] * mat[2])) * idet;
        ret[15] = (mat[0] * (mat[5] * mat[10] - mat[9] * mat[6]) - mat[4] * (mat[1] * mat[10] - mat[9] * mat[2]) + mat[8] * (mat[1] * mat[6] - mat[5] * mat[2])) * idet;
        return ret;
    }
    
    void zero() {
        mat[0] = 0.0; mat[4] = 0.0; mat[8] = 0.0; mat[12] = 0.0;
        mat[1] = 0.0; mat[5] = 0.0; mat[9] = 0.0; mat[13] = 0.0;
        mat[2] = 0.0; mat[6] = 0.0; mat[10] = 0.0; mat[14] = 0.0;
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 0.0;
    }
    void identity() {
        mat[0] = 1.0; mat[4] = 0.0; mat[8] = 0.0; mat[12] = 0.0;
        mat[1] = 0.0; mat[5] = 1.0; mat[9] = 0.0; mat[13] = 0.0;
        mat[2] = 0.0; mat[6] = 0.0; mat[10] = 1.0; mat[14] = 0.0;
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
    }
    void rotate(const vec3 &axis,float angle) {
        float rad = angle * DEG2RAD;
        float c = cos(rad);
        float s = sin(rad);
        vec3 v = axis;
        v.normalize();
        float xx = v.x * v.x;
        float yy = v.y * v.y;
        float zz = v.z * v.z;
        float xy = v.x * v.y;
        float yz = v.y * v.z;
        float zx = v.z * v.x;
        float xs = v.x * s;
        float ys = v.y * s;
        float zs = v.z * s;
        mat[0] = (1.0f - c) * xx + c; mat[4] = (1.0f - c) * xy - zs; mat[8] = (1.0f - c) * zx + ys; mat[12] = 0.0;
        mat[1] = (1.0f - c) * xy + zs; mat[5] = (1.0f - c) * yy + c; mat[9] = (1.0f - c) * yz - xs; mat[13] = 0.0;
        mat[2] = (1.0f - c) * zx - ys; mat[6] = (1.0f - c) * yz + xs; mat[10] = (1.0f - c) * zz + c; mat[14] = 0.0;
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
    }
    void rotate(float x,float y,float z,float angle) {
        rotate(vec3(x,y,z),angle);
    }
    void rotateX(float angle) {
        float rad = angle * DEG2RAD;
        float c = cos(rad);
        float s = sin(rad);
        mat[0] = 1.0; mat[4] = 0.0; mat[8] = 0.0; mat[12] = 0.0;
        mat[1] = 0.0; mat[5] = c; mat[9] = -s; mat[13] = 0.0;
        mat[2] = 0.0; mat[6] = s; mat[10] = c; mat[14] = 0.0;
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
    }
    void rotateY(float angle) {
        float rad = angle * DEG2RAD;
        float c = cos(rad);
        float s = sin(rad);
        mat[0] = c; mat[4] = 0.0; mat[8] = s; mat[12] = 0.0;
        mat[1] = 0.0; mat[5] = 1.0; mat[9] = 0.0; mat[13] = 0.0;
        mat[2] = -s; mat[6] = 0.0; mat[10] = c; mat[14] = 0.0;
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
    }
    void rotateZ(float angle) {
        float rad = angle * DEG2RAD;
        float c = cos(rad);
        float s = sin(rad);
        mat[0] = c; mat[4] = -s; mat[8] = 0.0; mat[12] = 0.0;
        mat[1] = s; mat[5] = c; mat[9] = 0.0; mat[13] = 0.0;
        mat[2] = 0.0; mat[6] = 0.0; mat[10] = 1.0; mat[14] = 0.0;
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
    }
    
    void scale(const vec3 &v) {
        mat[0] = v.x; mat[4] = 0.0; mat[8] = 0.0; mat[12] = 0.0;
        mat[1] = 0.0; mat[5] = v.y; mat[9] = 0.0; mat[13] = 0.0;
        mat[2] = 0.0; mat[6] = 0.0; mat[10] = v.z; mat[14] = 0.0;
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
    }
    void scale(float x,float y,float z) {
        scale(vec3(x,y,z));
    }
    void translate(const vec3 &v) {
        mat[0] = 1.0; mat[4] = 0.0; mat[8] = 0.0; mat[12] = v.x;
        mat[1] = 0.0; mat[5] = 1.0; mat[9] = 0.0; mat[13] = v.y;
        mat[2] = 0.0; mat[6] = 0.0; mat[10] = 1.0; mat[14] = v.z;
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
    }
    void translate(float x,float y,float z) {
        translate(vec3(x,y,z));
    }
    void reflect(const vec4 &plane) {
        float x = plane.x;
        float y = plane.y;
        float z = plane.z;
        float x2 = x * 2.0f;
        float y2 = y * 2.0f;
        float z2 = z * 2.0f;
        mat[0] = 1.0f - x * x2; mat[4] = -y * x2; mat[8] = -z * x2; mat[12] = -plane.w * x2;
        mat[1] = -x * y2; mat[5] = 1.0f - y * y2; mat[9] = -z * y2; mat[13] = -plane.w * y2;
        mat[2] = -x * z2; mat[6] = -y * z2; mat[10] = 1.0f - z * z2; mat[14] = -plane.w * z2;
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
    }
    void reflect(float x,float y,float z,float w) {
        reflect(vec4(x,y,z,w));
    }
    
    void ortho(float left, float right, float bottom, float top, float znear, float zfar) {
        mat[0] = 2.0f / (right - left); mat[4] = 0.0; mat[8] = 0.0; mat[12] = -(right + left) / (right - left);
        mat[1] = 0.0; mat[5] = 2.0f / (top - bottom); mat[9] = 0.0; mat[13] = -(top + bottom) / (top - bottom);
        mat[2] = 0.0; mat[6] = 0.0; mat[10] = -2.0f / (zfar - znear); mat[14] = -(zfar + znear) / (zfar - znear);
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0f;
    }
    void perspective(float fov, float aspect, float znear, float zfar) {
        if (fabs(fov - 90.0f) < EPSILON) fov = 89.9f;
        float y = tan(fov * MATH_PI / 360.0f);
        float x = y * aspect;
        mat[0] = 1.0f / x; mat[4] = 0.0; mat[8] = 0.0; mat[12] = 0.0;
        mat[1] = 0.0; mat[5] = 1.0f / y; mat[9] = 0.0; mat[13] = 0.0;
        mat[2] = 0.0; mat[6] = 0.0; mat[10] = -(zfar + znear) / (zfar - znear); mat[14] = -(2.0f * zfar * znear) / (zfar - znear);
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = -1.0; mat[15] = 0.0;
    }
    void lookAt(const vec3 &eye, const vec3 &dir, const vec3 &up) {
        vec3 x, y, z;
        mat4 m0, m1;
        z = eye - dir;
        z.normalize();
        x.cross(up, z);
        x.normalize();
        y.cross(z, x);
        y.normalize();
        m0[0] = x.x; m0[4] = x.y; m0[8] = x.z; m0[12] = 0.0;
        m0[1] = y.x; m0[5] = y.y; m0[9] = y.z; m0[13] = 0.0;
        m0[2] = z.x; m0[6] = z.y; m0[10] = z.z; m0[14] = 0.0;
        m0[3] = 0.0; m0[7] = 0.0; m0[11] = 0.0; m0[15] = 1.0;
        m1.translate(-eye);
        *this = m0 * m1;
    }
    void lookAt(float eye_x, float eye_y, float eye_z, float dir_x, float dir_y, float dir_z, float up_x, float up_y, float up_z) {
        lookAt(vec3(eye_x, eye_y, eye_z), vec3(dir_x, dir_y, dir_z), vec3(up_x, up_y, up_z));
    }
    
    union {
        struct {
            float m00, m10, m20, m30;
            float m01, m11, m21, m31;
            float m02, m12, m22, m32;
            float m03, m13, m23, m33;
        };
        float mat[16];
    };
};

    inline mat4 rotation(const mat4 &m) {
        return m.rotation();
    }
    
    inline mat4 transpose(const mat4 &m) {
        return m.transpose();
    }
    
    inline mat4 inverse(const mat4 &m) {
        return m.inverse();
    }
    
    inline mat4 rotate(const vec3 &axis, float angle) {
        mat4 m;
        m.rotate(axis, angle);
        return m;
    }
    
    inline mat4 rotate(float x, float y, float z, float angle) {
        return rotate(vec3(x, y, z), angle);
    }
    
    inline mat4 scale(const vec3 &v) {
        mat4 m;
        m.scale(v);
        return m;
    }
    
    inline mat4 scale(float x, float y, float z) {
        return scale(vec3(x, y, z));
    }
    
    inline mat4 translate(const vec3 &v) {
        mat4 m;
        m.translate(v);
        return m;
    }
    
    inline mat4 translate(float x, float y, float z) {
        return translate(vec3(x, y, z));
    }
    
    inline mat4 reflect(const vec4 &plane) {
        mat4 m;
        m.reflect(plane);
        return m;
    }
    
    inline mat4 reflect(float x, float y, float z, float w) {
        return reflect(vec4(x, y, z, w));
    }
    
    inline mat4 ortho(float left, float right, float bottom, float top, float znear, float zfar) {
        mat4 m;
        m.ortho(left, right, bottom, top, znear, zfar);
        return m;
    }
    
    inline mat4 perspective(float fov, float aspect, float znear, float zfar) {
        mat4 m;
        m.perspective(fov, aspect, znear, zfar);
        return m;
    }
    
    inline mat4 lookAt(const vec3 &eye, const vec3 &dir, const vec3 &up) {
        mat4 m;
        m.lookAt(eye, dir, up);
        return m;
    }
    
    inline mat4 lookAt(float eye_x, float eye_y, float eye_z, float dir_x, float dir_y, float dir_z, float up_x, float up_y, float up_z) {
        mat4 m;
        m.lookAt(eye_x, eye_y, eye_z, dir_x, dir_y, dir_z, up_x, up_y, up_z);
        return m;
    }
    
    inline mat4 yawPitchRoll
    (
     float yaw,
     float pitch,
     float roll
     )
    {
        float tmp_ch = cos(yaw);
        float tmp_sh = sin(yaw);
        float tmp_cp = cos(pitch);
        float tmp_sp = sin(pitch);
        float tmp_cb = cos(roll);
        float tmp_sb = sin(roll);
        
        mat4 Result;
        Result[0] = tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
        Result[1] = tmp_sb * tmp_cp;
        Result[2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
        Result[3] = 0;
        Result[4] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
        Result[5] = tmp_cb * tmp_cp;
        Result[6] = tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
        Result[7] = 0;
        Result[8] = tmp_sh * tmp_cp;
        Result[9] = -tmp_sp;
        Result[10] = tmp_ch * tmp_cp;
        Result[11] = 0;
        Result[12] = 0;
        Result[13] = 0;
        Result[14] = 0;
        Result[15] = 1;
        return Result;
    }

/*****************************************************************************/
/*                                                                           */
/* quat                                                                      */
/*                                                                           */
/*****************************************************************************/
    struct quat {
        
        quat() : x(0), y(0), z(0), w(1) { }
        quat(const vec3 &dir, float angle) {
            set(dir, angle);
        }
        quat(float x, float y, float z, float angle) {
            set(x, y, z, angle);
        }
        quat(const mat3 &m) {
            float trace = m[0] + m[4] + m[8];
            if (trace > 0.0) {
                float s = sqrt(trace + 1.0f);
                q[3] = 0.5f * s;
                s = 0.5f / s;
                q[0] = (m[5] - m[7]) * s;
                q[1] = (m[6] - m[2]) * s;
                q[2] = (m[1] - m[3]) * s;
            }
            else {
                static int next[3] = { 1, 2, 0 };
                int i = 0;
                if (m[4] > m[0]) i = 1;
                if (m[8] > m[3 * i + i]) i = 2;
                int j = next[i];
                int k = next[j];
                float s = sqrt(m[3 * i + i] - m[3 * j + j] - m[3 * k + k] + 1.0f);
                q[i] = 0.5f * s;
                if (s != 0) s = 0.5f / s;
                q[3] = (m[3 * j + k] - m[3 * k + j]) * s;
                q[j] = (m[3 * i + j] + m[3 * j + i]) * s;
                q[k] = (m[3 * i + k] + m[3 * k + i]) * s;
            }
        }
        
        operator float*() { return (float*)&x; }
        operator const float*() const { return (float*)&x; }
        
        float &operator[](int i) { return ((float*)&x)[i]; }
        const float operator[](int i) const { return ((float*)&x)[i]; }
        
        quat operator*(const quat &q) const {
            quat ret;
            ret.x = w * q.x + x * q.w + y * q.z - z * q.y;
            ret.y = w * q.y + y * q.w + z * q.x - x * q.z;
            ret.z = w * q.z + z * q.w + x * q.y - y * q.x;
            ret.w = w * q.w - x * q.x - y * q.y - z * q.z;
            return ret;
        }
        
        void set(const vec3 &dir, float angle) {
            float length = dir.length();
            if (length != 0.0) {
                length = 1.0f / length;
                float sinangle = sin(angle * DEG2RAD / 2.0f);
                x = dir[0] * length * sinangle;
                y = dir[1] * length * sinangle;
                z = dir[2] * length * sinangle;
                w = cos(angle * DEG2RAD / 2.0f);
            }
            else {
                x = y = z = 0.0;
                w = 1.0;
            }
        }
        void set(float x, float y, float z, float angle) {
            set(vec3(x, y, z), angle);
        }
        
        void slerp(const quat &q0, const quat &q1, float t) {
            float k0, k1, cosomega = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;
            quat q;
            if (cosomega < 0.0) {
                cosomega = -cosomega;
                q.x = -q1.x;
                q.y = -q1.y;
                q.z = -q1.z;
                q.w = -q1.w;
            }
            else {
                q.x = q1.x;
                q.y = q1.y;
                q.z = q1.z;
                q.w = q1.w;
            }
            if (1.0 - cosomega > 1e-6) {
                float omega = acos(cosomega);
                float sinomega = sin(omega);
                k0 = sin((1.0f - t) * omega) / sinomega;
                k1 = sin(t * omega) / sinomega;
            }
            else {
                k0 = 1.0f - t;
                k1 = t;
            }
            x = q0.x * k0 + q.x * k1;
            y = q0.y * k0 + q.y * k1;
            z = q0.z * k0 + q.z * k1;
            w = q0.w * k0 + q.w * k1;
        }
        
        mat3 toMatrix() const {
            mat3 ret;
            float x2 = x + x;
            float y2 = y + y;
            float z2 = z + z;
            float xx = x * x2;
            float yy = y * y2;
            float zz = z * z2;
            float xy = x * y2;
            float yz = y * z2;
            float xz = z * x2;
            float wx = w * x2;
            float wy = w * y2;
            float wz = w * z2;
            ret[0] = 1.0f - (yy + zz); ret[3] = xy - wz; ret[6] = xz + wy;
            ret[1] = xy + wz; ret[4] = 1.0f - (xx + zz); ret[7] = yz - wx;
            ret[2] = xz - wy; ret[5] = yz + wx; ret[8] = 1.0f - (xx + yy);
            return ret;
        }
        
        union {
            struct {
                float x, y, z, w;
            };
            float q[4];
        };
    };
    
    inline mat3::mat3(const quat &q) {
        mat3 m = q.toMatrix();
        mat[0] = m[0]; mat[3] = m[3]; mat[6] = m[6];
        mat[1] = m[1]; mat[4] = m[4]; mat[7] = m[7];
        mat[2] = m[2]; mat[5] = m[5]; mat[8] = m[8];
    }
    
    inline mat4::mat4(const quat &q) {
        mat3 m = q.toMatrix();
        mat[0] = m[0]; mat[4] = m[3]; mat[8] = m[6]; mat[12] = 0.0;
        mat[1] = m[1]; mat[5] = m[4]; mat[9] = m[7]; mat[13] = 0.0;
        mat[2] = m[2]; mat[6] = m[5]; mat[10] = m[8]; mat[14] = 0.0;
        mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
    }
    
    /*
     */
    inline quat slerp(const quat &q0, const quat &q1, float t) {
        quat ret;
        ret.slerp(q0, q1, t);
        return ret;
    }
    
    /*inline mat4 ConvertMatrix(btTransform &trn)
     {
     btVector3 R = trn.getBasis().getColumn(0);
     btVector3 U = trn.getBasis().getColumn(1);
     btVector3 L = trn.getBasis().getColumn(2);
     btVector3 P = trn.getOrigin();
     vec3 vR, vU, vL, vP;
     vR.x = R.x(); vR.y = R.y(); vR.z = R.z();
     vU.x = U.x(); vU.y = U.y(); vU.z = U.z();
     vL.x = L.x(); vL.y = L.y(); vL.z = L.z();
     vP.x = P.x(); vP.y = P.y(); vP.z = P.z();
     mat4 matOutput;
     matOutput[0] = vR.x; matOutput[1] = vR.y; matOutput[2] = vR.z; matOutput[3] = 0.f;
     matOutput[4] = vU.x; matOutput[5] = vU.y; matOutput[6] = vU.z; matOutput[7] = 0.f;
     matOutput[8] = vL.x; matOutput[9] = vL.y; matOutput[10] = vL.z; matOutput[11] = 0.f;
     matOutput[12] = vP.x; matOutput[13] = vP.y; matOutput[14] = vP.z; matOutput[15] = 1.f;
     return matOutput;
     }*/
}
NS_O_END