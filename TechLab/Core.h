#pragma once

// Containers
#include <vector>
#include <string>
#include <map>

#include <memory>
#include "Vector.h"
//#include "ObjectPicker.h"

template<typename T>
using TArray = std::vector<T>;
template<typename KeyType, typename ValueType>
using TMap = std::map<KeyType, ValueType>;
using FString = std::string;

// Typedef
typedef int int32;
typedef unsigned int uint32;

// Memory Allocation
struct MemoryHeader
{
    size_t Size;
    char _padding[8];
};

uint32& GetTotalAllocationBytes();
uint32& GetTotalAllocationCount();

void* operator new(size_t Size);
void operator delete(void* Ptr) noexcept;

void* operator new[](size_t Size);
void operator delete[](void* Ptr) noexcept;

// UClass

// [ UObject* function(void) ] Ptr
using StaticUObjectFactory = class UObject* (*)();

void UE_LogImpl(const char* fmt, ...);
#define UE_LOG(fmt, ...) UE_LogImpl(fmt, ##__VA_ARGS__)