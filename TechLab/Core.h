#pragma once

// Containers
#include <vector>
#include <string>
#include <map>

#include <memory>

#include "ImGuiAppConsole.h"
#include "ImGuiManager.h"

template<typename T>
using TArray = std::vector<T>;
template<typename KeyType, typename ValueType>
using TMap = std::map<KeyType, ValueType>;
using FString = std::string;

// Typedef
typedef int int32;
typedef unsigned int uint32;

// Memory Allocation
//extern uint32 TotalAllocationBytes;
//extern uint32 TotalAllocationCount;

struct MemoryHeader
{
    size_t Size;
    char _padding[8];
};

void* operator new(size_t Size) noexcept;
void operator delete(void* Ptr) noexcept;

void* operator new[](size_t Size) noexcept;
void operator delete[](void* Ptr) noexcept;

// UClass

// [ UObject* function(void) ] Ptr
using StaticUObjectFactory = class UObject* (*)();

#define UE_LOG(fmt, ...) \
    do \
    { \
        if (UImGuiManager::Get() && UImGuiManager::Get()->GetConsole()) UImGuiManager::Get()->GetConsole()->AddLog(fmt, ##__VA_ARGS__); \
    } while(0)
