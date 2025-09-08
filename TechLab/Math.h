#pragma once

static constexpr float PI = 3.1415926f;

__forceinline float DegreeToRadians(float Degree) { return Degree * (PI / 180.0f); }
float RadiansToDegree(float Radians);

#include <algorithm>
template<typename T>
constexpr T Max(const T& a, const T& b) 
{
    return std::max<T>(a, b);
}
template<typename T>
constexpr T Min(const T& a, const T& b) 
{
    return std::min<T>(a, b);
}
