#pragma once
#include "Vector.h"
static constexpr float PI = 3.1415926f;

__forceinline float DegreeToRadians(float Degree) { return Degree * (PI / 180.0f); }
FVector DegreeToRadians(const FVector& Degree);
float RadiansToDegree(float Radians);
FVector RadiansToDegree(const FVector& Radians);

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
template<typename T>
const T& Clamp(const T& value, const T& minValue, const T& maxValue)
{
    if (value < minValue) return minValue;
    if (value > maxValue) return maxValue;
    return value;
}