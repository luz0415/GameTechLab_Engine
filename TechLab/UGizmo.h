#pragma once
#include "Core.h"
#include "MeshResource.h"
#include "SceneComponent.h"
#include "PrimitiveComponent.h"
enum class EGizmoAxis { X, Y, Z };

class UGizmo : public UPrimitiveComponent
{
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
    virtual void HandleDrag(int x, int y, int z);

protected:
    FString Name;
};