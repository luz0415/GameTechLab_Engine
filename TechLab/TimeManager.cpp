#include "TimeManager.h"

FTimeManager::FTimeManager() : DeltaTime(0.0), TargetFrameTime(0.0) {}

void FTimeManager::Init()
{
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&PrevTime);
}

void FTimeManager::Update()
{
    LARGE_INTEGER CurrentTime;
    QueryPerformanceCounter(&CurrentTime);
    double ActualDeltaTime = static_cast<double>(CurrentTime.QuadPart - PrevTime.QuadPart) / Frequency.QuadPart;

    if (TargetFPS > 0)
    {
        TargetFrameTime = 1.0 / TargetFPS;

        if (ActualDeltaTime < TargetFrameTime)
        {
            double RemainingTime = TargetFrameTime - ActualDeltaTime;
            Sleep(static_cast<DWORD>(RemainingTime * 1000));
            QueryPerformanceCounter(&CurrentTime);
            DeltaTime = static_cast<double>(CurrentTime.QuadPart - PrevTime.QuadPart) / Frequency.QuadPart;
        }
        else
        {
            DeltaTime = ActualDeltaTime;
        }
    }
    else
    {
        DeltaTime = ActualDeltaTime;
    }
    PrevTime = CurrentTime;
}
