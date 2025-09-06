#include "Vector4.h"
#include "Vector.h"
#include <cassert>

FVector4::FVector4(const FVector& V3, float InW)
    : X(V3.X), Y(V3.Y), Z(V3.Z), W(InW)
{
}

float FVector4::Dot(const FVector4& Other) const noexcept
{
    return X * Other.X + Y * Other.Y + Z * Other.Z + W * Other.W;
}

FVector4 FVector4::operator+(const FVector4& Other) const noexcept
{
    return FVector4(X + Other.X, Y + Other.Y, Z + Other.Z, W + Other.W);
}

FVector4 FVector4::operator-(const FVector4& Other) const noexcept
{
    return FVector4(X - Other.X, Y - Other.Y, Z - Other.Z, W - Other.W);
}

FVector4 FVector4::operator*(float Scale) const noexcept
{
    return FVector4(X * Scale, Y * Scale, Z * Scale, W * Scale);
}

FVector4 FVector4::operator/(float Scale) const noexcept
{
    assert(std::fabs(Scale) > KINDA_SMALL_NUMBER_V4);
    const float InvScale = 1.0f / Scale;
    return FVector4(X * InvScale, Y * InvScale, Z * InvScale, W * InvScale);
}

FVector4 FVector4::operator-() const noexcept
{
    return FVector4(-X, -Y, -Z, -W);
}

FVector4& FVector4::operator+=(const FVector4& Other) noexcept
{
    X += Other.X; Y += Other.Y; Z += Other.Z; W += Other.W;
    return *this;
}

FVector4& FVector4::operator-=(const FVector4& Other) noexcept
{
    X -= Other.X; Y -= Other.Y; Z -= Other.Z; W -= Other.W;
    return *this;
}

FVector4& FVector4::operator*=(float Scale) noexcept
{
    X *= Scale; Y *= Scale; Z *= Scale; W *= Scale;
    return *this;
}

FVector4& FVector4::operator/=(float Scale) noexcept
{
    assert(std::fabs(Scale) > KINDA_SMALL_NUMBER_V4);
    const float InvScale = 1.0f / Scale;
    X *= InvScale; Y *= InvScale; Z *= InvScale; W *= InvScale;
    return *this;
}

bool FVector4::operator==(const FVector4& Other) const noexcept
{
    return (*this - Other).IsNearlyZero();
}

bool FVector4::operator!=(const FVector4& Other) const noexcept
{
    return !(*this == Other);
}

float FVector4::Length() const noexcept
{
    return std::sqrt(X * X + Y * Y + Z * Z + W * W);
}

float FVector4::LengthSquared() const noexcept
{
    return X * X + Y * Y + Z * Z + W * W;
}

void FVector4::Normalize() noexcept
{
    const float Mag = Length();
    if (Mag > KINDA_SMALL_NUMBER_V4)
    {
        const float InvMag = 1.0f / Mag;
        X *= InvMag; Y *= InvMag; Z *= InvMag; W *= InvMag;
    }
}

FVector4 FVector4::GetNormalized() const noexcept
{
    FVector4 Copy = *this;
    Copy.Normalize();
    return Copy;
}

bool FVector4::IsNearlyZero(float Tolerance) const noexcept
{
    return LengthSquared() < (Tolerance * Tolerance);
}
