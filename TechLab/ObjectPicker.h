#pragma once
#include <vector>

class IPickable;
class UCamera;
struct FRay;
struct FHitResult;
class UGizmoRenderer;
struct FMatrix;

class UObjectPicker
{
public:
    UObjectPicker();
    ~UObjectPicker();

    void HandleMouseClick(float ScreenX, float ScreenY);
    void HandleMouseDrag(float ScreenX, float ScreenY);
    void SetViewportSize(int Width, int Height) { ViewportWidth = Width; ViewportHeight = Height; }
    IPickable* GetCurrentSelection() const;

    void SetCamera(UCamera* camera);

    void SubmitProxy();
    void HandleMouseRelease();

    void SetIsDragging(bool b) { bIsDragging = b; }
    bool GetIsDragging() { return bIsDragging; }

private:
    FRay CreateRayFromScreen(float ScreenX, float ScreenY) const;
    FRay TransformRayToLocalSpace(const FRay& WorldRay, const FMatrix& WorldTransform) const;

    void UpdateSelection(IPickable* NewSelection);
    void ClearSelection();

    UCamera* Camera;

    int ViewportWidth = 1;
    int ViewportHeight = 1;
    bool bIsDragging = false;
    IPickable* CurrentSelection = nullptr;
    IPickable* DraggedObject = nullptr;
    UGizmoRenderer* GizmoRenderer = nullptr;
};
