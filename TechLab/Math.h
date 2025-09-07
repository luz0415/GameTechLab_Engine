#pragma once

static constexpr float PI = 3.1415926f;

static __forceinline float DegreeToRadians(float Degree) { return Degree * (PI / 180.0f); }
static float RadiansToDegree(float Radians);
