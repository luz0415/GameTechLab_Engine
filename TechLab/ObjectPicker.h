#pragma once
#include <vector>

class IPickable;
class UCamera;
struct FRay;
struct FHitResult;

class ObjectPicker
{
public:
    ObjectPicker(UCamera* camera);
    ~ObjectPicker() {};

    void HandleMouseClick(float ScreenX, float ScreenY);
    void SetViewportSize(int Width, int Height) { ViewportWidth = Width; ViewportHeight = Height; }
    const std::vector<IPickable*>& GetCurrentSelection() const;

private:
    FRay CreateRayFromScreen(float ScreenX, float ScreenY) const;

    void UpdateSelection(IPickable* NewSelection);
    void ClearSelection();

    UCamera* Camera;

    int ViewportWidth = 1;
    int ViewportHeight = 1;

    std::vector<IPickable*> CurrentSelections;
};
