#pragma once
#include "VisualInterface.h"
#include "Core.h"
#include "MeshResource.h"
#include "SceneComponent.h"
#include "PrimitiveComponent.h"
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
    void SetName(const FString& InName) { Name = InName; }
    const FString& GetName() {return Name;}
    void SetPickedItem(USceneComponent* Item) { SetAttachment(Item); }


private:
    FString Name;
};