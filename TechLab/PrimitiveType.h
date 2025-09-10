#pragma once
#include "Core.h"

enum class EPrimitiveType
{
	Custom,
	Cube,
	Sphere,
    Ring,
};

inline FString PrimitiveTypeToString(EPrimitiveType Type)
{
    switch (Type)
    {
    case EPrimitiveType::Custom:
        return FString("Custom");
    case EPrimitiveType::Cube:
        return FString("Cube");
    case EPrimitiveType::Sphere:
        return FString("Sphere");
    case EPrimitiveType::Ring:
            return FString("Ring");
    default:
        return FString("Default");
    }
}

inline EPrimitiveType StringToPrimitiveType(const FString& Str)
{
    if (Str == "Custom")
        return EPrimitiveType::Custom;
    else if (Str == "Cube")
        return EPrimitiveType::Cube;
    else if (Str == "Sphere")
        return EPrimitiveType::Sphere;
    else if (Str == "Ring")
        return EPrimitiveType::Ring;
    else
        return EPrimitiveType::Custom;
}
