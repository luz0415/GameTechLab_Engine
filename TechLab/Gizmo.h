#pragma once
#include "Core.h"
#include "MeshResource.h"
#include "SceneComponent.h"
#include "PrimitiveComponent.h"

class UCamera;
enum class EGizmoAxis { X, Y, Z };

class UGizmo : public UPrimitiveComponent
{
public:
    static UObject* StaticUObjectFactory()
    {
        return new UGizmo();
    }

    static UClass* StaticClass()
    {
        static UClass Class(FString("UGizmo"), StaticUObjectFactory, UPrimitiveComponent::StaticClass());
        return &Class;
    }

    virtual UClass* GetClass() const
    {
        return StaticClass();
    }

public:
    UGizmo();
    ~UGizmo() override;
    void SetName(const FString& InName);
    const FString& GetName() { return Name; }
    void SetPickedItem(USceneComponent* Item) { SetAttachment(Item); }
    virtual bool CanPickable() { if (GetAttachment()) return true; return false; }
    virtual void SubmitProxy() override;
    virtual void SetAxis(EGizmoAxis InAxis);
    virtual void HandleDrag(UCamera* Camera, const FVector& RayOrigin, const FVector& RayDirection);
    virtual FVector GetIntersectionWithMovementPlane(UCamera* Camera, FVector RayOrigin, FVector RayDirection);
    virtual void OnDragStart(UCamera* Camera, const FVector& RayOrigin, const FVector& RayDirection);
protected:
    bool bIsDragging = false;
    FVector InitialHitPoint;
    FVector InitialObjectPosition;
    FString Name;
    FVector Direction;
};