#pragma once
#include <vector>

class IPickable;
class UCamera;
struct FRay;
struct FMatrix;

class UObjectPicker
{
public:
    UObjectPicker();
    ~UObjectPicker() {};

    void HandleMouseClick(float ScreenX, float ScreenY);
    void SetViewportSize(int Width, int Height) { ViewportWidth = Width; ViewportHeight = Height; }
    const std::vector<IPickable*>& GetCurrentSelection() const;

    void SetCamera(UCamera* camera);

private:
    FRay CreateRayFromScreen(float ScreenX, float ScreenY) const;
    FRay TransformRayToLocalSpace(const FRay& WorldRay, const FMatrix& WorldTransform) const;

    void UpdateSelection(IPickable* NewSelection);
    void ClearSelection();

    UCamera* Camera;

    int ViewportWidth = 1;
    int ViewportHeight = 1;

    std::vector<IPickable*> CurrentSelections;
};
