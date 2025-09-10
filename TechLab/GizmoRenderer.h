#pragma once
#include "Gizmo.h"
#include "Core.h"
#include "MeshResource.h"
#include <functional>
#include "PrimitiveComponent.h"

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
    const USceneComponent* GetPickedItem() const { return GetAttachment(); }
    
private:
    TArray<UGizmo*> Gizmos;
};