#pragma once
#include "Core.h"
#include "Windows.h"

class FTimeManager
{
private:
    FTimeManager();
    ~FTimeManager() = default;

public:
    static FTimeManager* Get()
    {
        static FTimeManager Instance;
        return &Instance;
    }

    void Init();
    void Update();

    uint32 GetCurrentFPS() const { return static_cast<uint32>(1.0f / DeltaTime); }

    double GetDeltaTime() const { return DeltaTime * TimeScale; }
    double GetRealDeltaTime() const { return DeltaTime; }

    void SetTimeScale(float inTimeScale) { TimeScale = inTimeScale; }
    float GetTimeScale() const { return TimeScale; }

    // 0 Is No Limit
    void SetTargetFPS(uint32 fps) { TargetFPS = fps; }
    uint32 GetTargetFPS() const { return TargetFPS; }

private:
    float TimeScale = 1.0f;

    LARGE_INTEGER Frequency;
    LARGE_INTEGER PrevTime;
    double DeltaTime;
    double TargetFrameTime;

    uint32 TargetFPS = 0;
};

