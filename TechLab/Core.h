#pragma once

// Containers
#include <vector>
#include <string>
#include <map>

template<typename T>
using TArray = std::vector<T>;
template<typename KeyType, typename ValueType>
using TMap = std::map<KeyType, ValueType>;
using FString = std::string;

// Typedef
typedef int int32;
typedef unsigned int uint32;

// Memory Allocation
extern uint32 TotalAllocationBytes;
extern uint32 TotalAllocationCount;

struct MemoryHeader
{
    size_t Size;
};

void* operator new(size_t Size) noexcept;
void operator delete(void* Ptr) noexcept;

void* operator new[](size_t Size) noexcept;
void operator delete[](void* Ptr) noexcept;

// UClass

// [ UObject* function(void) ] Ptr
using StaticClassFactory = class UObject* (*)();
