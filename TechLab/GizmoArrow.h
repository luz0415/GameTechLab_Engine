#pragma once
#include "VisualInterface.h"
#include "Core.h"
#include "MeshResource.h"
#include "SceneComponent.h"
#include "PrimitiveComponent.h"

enum class EGizmoArrowAxis { X, Y, Z };

class UGizmoArrow : public UPrimitiveComponent
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
    void SubmitProxy() override;
    void SetName(const FString& InName);
    const FString& GetName() { return Name; }
    void SetPickedItem(USceneComponent* Item) { SetAttachment(Item); }
    virtual bool CanPickable() { if (GetAttachment()) return true; return false; }
    void SetArrowAxis(EGizmoArrowAxis InAxis);

private:
    FString Name;
};