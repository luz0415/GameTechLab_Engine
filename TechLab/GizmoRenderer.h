#pragma once
#include "Gizmo.h"
#include "Core.h"
#include "MeshResource.h"
#include <functional>
#include "PrimitiveComponent.h"

enum class GizmoType
{
    Arrow,
    Scale,
    Torus
};

class UGizmoRenderer : public UPrimitiveComponent
{
public:
    static UObject* StaticUObjectFactory()
    {
        return new UGizmoRenderer();
    }

    static UClass* StaticClass()
    {
        static UClass Class(FString("UGizmoRenderer"), StaticUObjectFactory, UPrimitiveComponent::StaticClass());
        return &Class;
    }

    virtual UClass* GetClass() const
    {
        return StaticClass();
    }

    UGizmoRenderer();
    ~UGizmoRenderer() override;
    virtual void SubmitProxy() override;
    void SetPickedItem(UObject* Item);
    FMeshData MakeTorus(EGizmoAxis InAxis);
    const USceneComponent* GetPickedItem() const { return GetAttachment(); }
    
private:
    TArray<TArray<UGizmo*>> Gizmos;
    GizmoType Type = GizmoType::Arrow;
};