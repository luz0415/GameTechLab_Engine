#pragma once
#include "FGizmoArrow.h"
#include "Core.h"
#include "MeshResource.h"
#include <functional>
#include "PrimitiveComponent.h"

class FGizmoRenderer : public UPrimitiveComponent
{
public:
    static UObject* StaticUObjectFactory()
    {
        return new FGizmoRenderer();
    }

    static UClass* StaticClass()
    {
        static UClass Class(FString("FGizmoRenderer"), StaticUObjectFactory, USceneComponent::StaticClass());
        return &Class;
    }

    virtual UClass* GetClass() const
    {
        return StaticClass();
    }

    FGizmoRenderer();
    ~FGizmoRenderer() override;
    virtual void SubmitProxy() override;
    void SetPickedItem(UObject* Item);
    const USceneComponent* GetPickedItem() const { return GetAttachment(); }
    
private:
    TArray<FGizmoArrow> Arrows;
};