#include "Core.h"
#include <malloc.h>
//uint32 TotalAllocationBytes = 0;
//uint32 TotalAllocationCount = 0;

uint32& GetTotalAllocationBytes()
{
    static uint32 Instance = 0;
    return Instance;
}

uint32& GetTotalAllocationCount()
{
    static uint32 Instance = 0;
    return Instance;
}

void* operator new(size_t Size)
{
    constexpr size_t Alignment = 16;
    size_t TotalSize = Size + sizeof(MemoryHeader);
    void* Ptr = _aligned_malloc(TotalSize, Alignment);
    if (Ptr == nullptr) { throw std::bad_alloc(); }

    MemoryHeader* Header = static_cast<MemoryHeader*>(Ptr);
    Header->Size = Size;
    GetTotalAllocationCount()++;
    GetTotalAllocationBytes() += static_cast<uint32>(TotalSize);
    return static_cast<void*>(reinterpret_cast<char*>(Ptr) + sizeof(MemoryHeader));
}

void operator delete(void* Ptr) noexcept {
    if (!Ptr) { return; }

    void* HeaderPtr = static_cast<void*>(reinterpret_cast<char*>(Ptr) - sizeof(MemoryHeader));
    MemoryHeader* Header = static_cast<MemoryHeader*>(HeaderPtr);
    size_t OriginalSize = Header->Size;
    size_t TotalSize = OriginalSize + sizeof(MemoryHeader);
    GetTotalAllocationCount()--;
    GetTotalAllocationBytes() -= static_cast<uint32>(TotalSize);
    _aligned_free(HeaderPtr);
}

void* operator new[](size_t Size)
{
    constexpr size_t Alignment = 16;
    size_t TotalSize = Size + sizeof(MemoryHeader);
    void* Ptr = _aligned_malloc(TotalSize, Alignment);
    if (Ptr == nullptr) { throw std::bad_alloc(); }

    MemoryHeader* Header = static_cast<MemoryHeader*>(Ptr);
    Header->Size = Size;

    GetTotalAllocationCount()++;
    GetTotalAllocationBytes() += static_cast<uint32>(TotalSize);

    return static_cast<void*>(reinterpret_cast<char*>(Ptr) + sizeof(MemoryHeader));
}

void operator delete[](void* Ptr) noexcept
{
    if (!Ptr) return;

    void* HeaderPtr = static_cast<void*>(reinterpret_cast<char*>(Ptr) - sizeof(MemoryHeader));
    MemoryHeader* Header = static_cast<MemoryHeader*>(HeaderPtr);

    size_t OriginalSize = Header->Size;
    size_t TotalSize = OriginalSize + sizeof(MemoryHeader);

    GetTotalAllocationCount()--;
    GetTotalAllocationBytes() -= static_cast<uint32>(TotalSize);

    _aligned_free(HeaderPtr);
}