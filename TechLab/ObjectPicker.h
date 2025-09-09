#pragma once
#include <vector>

class IPickable;
class UCamera;
struct FRay;
struct FHitResult;
class FGizmoRenderer;
class UObjectPicker
{
public:
    UObjectPicker();
    ~UObjectPicker() {};

    void HandleMouseClick(float ScreenX, float ScreenY);
    void SetViewportSize(int Width, int Height) { ViewportWidth = Width; ViewportHeight = Height; }
    const std::vector<IPickable*>& GetCurrentSelection() const;

    void SetCamera(UCamera* camera);

    void SubmitProxy();

private:
    FRay CreateRayFromScreen(float ScreenX, float ScreenY) const;

    void UpdateSelection(IPickable* NewSelection);
    void ClearSelection();

    UCamera* Camera;

    int ViewportWidth = 1;
    int ViewportHeight = 1;

    std::vector<IPickable*> CurrentSelections;
    FGizmoRenderer* GizmoRenderer = nullptr;
};
