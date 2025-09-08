#include "Core.h"
#include <malloc.h>
//uint32 TotalAllocationBytes = 0;
//uint32 TotalAllocationCount = 0;

uint32& GetTotalAllocationBytes()
{
    static uint32 Instance = 0; // 함수가 처음 호출될 때 단 한 번 0으로 초기화됩니다.
    return Instance;
}

uint32& GetTotalAllocationCount()
{
    static uint32 Instance = 0; // 위와 동일
    return Instance;
}


void* operator new(size_t Size) noexcept {
    constexpr size_t alignment = 16;
    size_t TotalSize = Size + sizeof(MemoryHeader);
    void* Ptr = _aligned_malloc(TotalSize,alignment);
    if (Ptr == nullptr) { return nullptr; }

    MemoryHeader* Header = static_cast<MemoryHeader*>(Ptr);
    Header->Size = Size;
    GetTotalAllocationCount()++;
    GetTotalAllocationBytes() += TotalSize;
    return static_cast<void*>(reinterpret_cast<char*>(Ptr) + sizeof(MemoryHeader));
}

void operator delete(void* Ptr) noexcept {
    if (!Ptr) { return; }

    void* HeaderPtr = static_cast<void*>(reinterpret_cast<char*>(Ptr) - sizeof(MemoryHeader));
    MemoryHeader* Header = static_cast<MemoryHeader*>(HeaderPtr);
    size_t OriginalSize = Header->Size;
    size_t TotalSize = OriginalSize + sizeof(MemoryHeader);
    GetTotalAllocationCount()--;
    GetTotalAllocationBytes() -= TotalSize;
    _aligned_free(HeaderPtr);
}

void* operator new[](size_t Size) noexcept
{
    constexpr size_t alignment = 16;
    size_t totalSize = Size + sizeof(MemoryHeader);
    void* Ptr = _aligned_malloc(totalSize,alignment);
    if (Ptr == nullptr) { return nullptr; }

    MemoryHeader* header = static_cast<MemoryHeader*>(Ptr);
    header->Size = Size;

    GetTotalAllocationCount()++;
    GetTotalAllocationBytes() += totalSize;

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
    GetTotalAllocationBytes() -= TotalSize;

    _aligned_free(HeaderPtr);
}