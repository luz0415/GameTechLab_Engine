#pragma once
#include "VisualInterface.h"
#include "Core.h"
#include "MeshResource.h"
#include "SceneComponent.h"
#include "Gizmo.h"
#include "PrimitiveComponent.h"

class UGizmoRotation : public UGizmo
{
public:
    static UObject* StaticUObjectFactory()
    {
        return new UGizmoRotation();
    }

    static UClass* StaticClass()
    {
        static UClass Class(FString("UGizmoRotation"), StaticUObjectFactory, UPrimitiveComponent::StaticClass());
        return &Class;
    }

    virtual UClass* GetClass() const
    {
        return StaticClass();
    }

public:
    UGizmoRotation();
    ~UGizmoRotation() override;
    
    //virtual void SubmitProxy() override;
    //    virtual bool CanPickable() { if (GetAttachment()) return true; return false; }
    virtual void SetAxis(EGizmoAxis InAxis) override;
    virtual void HandleDrag(UCamera* Camera, const FVector& RayOrigin, const FVector& RayDirection) override;
    virtual void OnDragStart(UCamera* Camera, const FVector& RayOrigin, const FVector& RayDirection) override;
    //    virtual FVector GetIntersectionWithMovementPlane(UCamera* Camera, FVector RayOrigin, FVector RayDirection) override;


private:
    //FVector LastIntersectionPoint;
    FVector RotationAxis;
    FQuaternion InitialObjectRotation;
    FVector InitialVectorOnPlane;
    float DragSensitivity = 0.1f;
};

