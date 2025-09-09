#pragma once
#include "VisualInterface.h"
#include "Core.h"
#include "MeshResource.h"
#include "SceneComponent.h"
#include "PrimitiveComponent.h"
class FGizmoArrow : public UPrimitiveComponent
{
public:
    FGizmoArrow();
    ~FGizmoArrow() override;
    void SubmitProxy() override;
    void SetName(FString name) { Name = name; }
    const FString& GetName() {return Name;}
    void SetPickedItem(USceneComponent* Item) { SetAttachment(Item); }


private:
    FString Name;
};