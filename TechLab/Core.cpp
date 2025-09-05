#include "Core.h"

uint32 TotalAllocationBytes = 0;
uint32 TotalAllocationCount = 0;

void* operator new(size_t Size) noexcept {
    size_t TotalSize = Size + sizeof(MemoryHeader);
    void* Ptr = malloc(TotalSize);
    if (Ptr == nullptr) { return nullptr; }

    MemoryHeader* Header = static_cast<MemoryHeader*>(Ptr);
    Header->Size = Size;
    TotalAllocationCount++;
    TotalAllocationBytes += TotalSize;
    return static_cast<void*>(reinterpret_cast<char*>(Ptr) + sizeof(MemoryHeader));
}

void operator delete(void* Ptr) noexcept {
    if (!Ptr) { return; }

    void* HeaderPtr = static_cast<void*>(reinterpret_cast<char*>(Ptr) - sizeof(MemoryHeader));
    MemoryHeader* Header = static_cast<MemoryHeader*>(HeaderPtr);
    size_t OriginalSize = Header->Size;
    size_t TotalSize = OriginalSize + sizeof(MemoryHeader);
    TotalAllocationCount--;
    TotalAllocationBytes -= TotalSize;
    free(HeaderPtr);
}

void* operator new[](size_t Size) noexcept
{
    size_t totalSize = Size + sizeof(MemoryHeader);
    void* Ptr = malloc(totalSize);
    if (Ptr == nullptr) { return nullptr; }

    MemoryHeader* header = static_cast<MemoryHeader*>(Ptr);
    header->Size = Size;

    TotalAllocationCount++;
    TotalAllocationBytes += totalSize;

    return static_cast<void*>(reinterpret_cast<char*>(Ptr) + sizeof(MemoryHeader));

}

void operator delete[](void* Ptr) noexcept
{
    if (!Ptr) return;

    void* HeaderPtr = static_cast<void*>(reinterpret_cast<char*>(Ptr) - sizeof(MemoryHeader));
    MemoryHeader* Header = static_cast<MemoryHeader*>(HeaderPtr);

    size_t OriginalSize = Header->Size;
    size_t TotalSize = OriginalSize + sizeof(MemoryHeader);

    TotalAllocationCount--;
    TotalAllocationBytes -= TotalSize;

    free(HeaderPtr);
}
