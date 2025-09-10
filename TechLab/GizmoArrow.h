#pragma once
#include "VisualInterface.h"
#include "Core.h"
#include "MeshResource.h"
#include "SceneComponent.h"
#include "UGizmo.h"
#include "PrimitiveComponent.h"

class UGizmoArrow : public UGizmo
{
public:
    static UObject* StaticUObjectFactory()
    {
        return new UGizmoArrow();
    }

    static UClass* StaticClass()
    {
        static UClass Class(FString("UGizmoArrow"), StaticUObjectFactory, UPrimitiveComponent::StaticClass());
        return &Class;
    }

    virtual UClass* GetClass() const
    {
        return StaticClass();
    }

public:
    UGizmoArrow();
    ~UGizmoArrow() override;
    virtual void SubmitProxy() override;
//    virtual bool CanPickable() { if (GetAttachment()) return true; return false; }
    virtual void SetAxis(EGizmoAxis InAxis) override;
    virtual void HandleDrag(int x, int y, int z);

};