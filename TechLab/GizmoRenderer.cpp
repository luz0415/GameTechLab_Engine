#include "GizmoRenderer.h"
#include "Shapes.h"
#include "Renderer.h"
#include "SceneComponent.h"
#include "Core.h"
#include "ImGuiManager.h"
#include "GizmoArrow.h"
#include "GizmoRotation.h"
#include "GizmoScale.h"
UGizmoRenderer::UGizmoRenderer()
{
	//Init();
	URenderer::Get()->RegisterMesh(FString("ArrowZ"), Shapes::ArrowZ_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	URenderer::Get()->RegisterMesh(FString("ArrowY"), Shapes::ArrowY_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	URenderer::Get()->RegisterMesh(FString("ArrowX"), Shapes::ArrowX_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    URenderer::Get()->RegisterMesh(FString("ScaleX"), Shapes::ScaleX_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    URenderer::Get()->RegisterMesh(FString("ScaleY"), Shapes::ScaleY_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    URenderer::Get()->RegisterMesh(FString("ScaleZ"), Shapes::ScaleZ_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	URenderer::Get()->RegisterMesh(FString("TorusX"), MakeTorus(EGizmoAxis::X), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    URenderer::Get()->RegisterMesh(FString("TorusY"), MakeTorus(EGizmoAxis::Y), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    URenderer::Get()->RegisterMesh(FString("TorusZ"), MakeTorus(EGizmoAxis::Z), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UGizmoArrow* ArrowZ = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowZ->SetAxis(EGizmoAxis::Z);
	UGizmoArrow* ArrowY = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowY->SetAxis(EGizmoAxis::Y);
	UGizmoArrow* ArrowX = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowX->SetAxis(EGizmoAxis::X);
    
    UGizmoScale* ScaleX = FObjectFactory::Get()->ConstructObject<UGizmoScale>();
    ScaleX->SetAxis(EGizmoAxis::X);
    UGizmoScale* ScaleY = FObjectFactory::Get()->ConstructObject<UGizmoScale>();
    ScaleY->SetAxis(EGizmoAxis::Y);
    UGizmoScale* ScaleZ = FObjectFactory::Get()->ConstructObject<UGizmoScale>();
    ScaleZ->SetAxis(EGizmoAxis::Z);

	UGizmoRotation* RotationZ = FObjectFactory::Get()->ConstructObject<UGizmoRotation>();
	RotationZ->SetAxis(EGizmoAxis::Z);
	UGizmoRotation* RotationY = FObjectFactory::Get()->ConstructObject<UGizmoRotation>();
	RotationY->SetAxis(EGizmoAxis::Y);
	UGizmoRotation* RotationX = FObjectFactory::Get()->ConstructObject<UGizmoRotation>();
	RotationX->SetAxis(EGizmoAxis::X);


    TArray<UGizmo*> Arrows;
    TArray<UGizmo*> Scales;
    TArray<UGizmo*> Toruses;
    
    Arrows.push_back(ArrowZ);
    Arrows.push_back(ArrowY);
    Arrows.push_back(ArrowX);
    Scales.push_back(ScaleX);
    Scales.push_back(ScaleY);
    Scales.push_back(ScaleZ);
    Toruses.push_back(RotationZ);
    Toruses.push_back(RotationY);
    Toruses.push_back(RotationX);
    
    Gizmos.push_back(Arrows);
    Gizmos.push_back(Scales);
    Gizmos.push_back(Toruses);
}

UGizmoRenderer::~UGizmoRenderer()
{
	for (auto& GizmoType : Gizmos)
	{
        for(auto& Gizmo : GizmoType )
		if (FObjectFactory::Get()->IsObjectValid(Gizmo))
		{
            Gizmo->Destroy();
		}
	}
}

void UGizmoRenderer::SubmitProxy()
{
	if (GetAttachment() != nullptr)
	{
		//UE_LOG("PickedItem : [%f , %f , %f]", PickedItem->GetWorldLocation().X, PickedItem->GetWorldLocation().Y, PickedItem->GetWorldLocation().Z);
		for (auto& Gizmo : Gizmos[(int)Type])
		{
			Gizmo->SubmitProxy();
			//Arrow.SubmitProxy(FMatrix::ScaleMatrix(FVector(3.0f, 3.0f, 3.0f)));
		}
	}
}

void UGizmoRenderer::SetPickedItem(UObject* Item)
{
    Type = GizmoType::Scale;
	if (Item && 
		((Item->IsA(UGizmoArrow::StaticClass())
			||(Item->IsA(UGizmoRotation::StaticClass()))
            ||(Item->IsA(UGizmoScale::StaticClass()))
		))) { return; }

	if (USceneComponent* Comp = Cast<USceneComponent>(Item))
	{
		UE_LOG("FGIZMORENDERER : PICKED");
		SetAttachment(Comp);
		for (auto& GizmoList : Gizmos)
		{
            for (auto& Gizmo : GizmoList)
            {
                Gizmo->SetWorldLocation(Comp->GetWorldLocation());
                Gizmo->SetWorldScale(Comp->GetWorldScale() * 3);
                Gizmo->SetPickedItem(Comp);
            }
			//Arrow->SetWorldRotation(GetWorldRotationAsQuaternion()*Arrow->GetWorldRotationAsQuaternion());
		}
	}
	else
	{
		UE_LOG("FGIZMORENDERER : No SceneComponent");
		Detach();
        for (auto& GizmoList : Gizmos)
        {
            for (auto& Gizmo : GizmoList)
            {
                Gizmo->Detach();
            }
        }
		return;
	}
}

FMeshData UGizmoRenderer::MakeTorus(EGizmoAxis InAxis)
{
    float majorRadius = 1.0f;
    float minorRadius = 0.1f;
    int majorSegments = 32;
    int minorSegments = 16;

    TArray<FVertex> Vertices;
    TArray<uint32> Indices;

    for (int i = 0; i <= majorSegments; ++i) {
        float theta = (float)i / majorSegments * 2.0f * PI;
        float cosTheta = cos(theta);
        float sinTheta = sin(theta);

        for (int j = 0; j <= minorSegments; ++j) {
            float phi = (float)j / minorSegments * 2.0f * PI;
            float cosPhi = cos(phi);
            float sinPhi = sin(phi);

            FVector basePos;
            basePos.X = (majorRadius + minorRadius * cosPhi) * cosTheta;
            basePos.Y = (majorRadius + minorRadius * cosPhi) * sinTheta;
            basePos.Z = minorRadius * sinPhi;

            FVertex vertex;
            FVector finalPos;
            FVector4 finalColor;

            switch (InAxis)
            {
            case EGizmoAxis::X: 
                finalPos.X = basePos.Z;
                finalPos.Y = basePos.Y;
                finalPos.Z = -basePos.X;
                finalColor = FVector4(1.f, 0.f, 0.f, .2f);
                break;

            case EGizmoAxis::Y: 
                finalPos.X = basePos.X;
                finalPos.Y = basePos.Z;
                finalPos.Z = -basePos.Y;
                finalColor = FVector4(0.f, 1.f, 0.f, .2f);
                break;

            case EGizmoAxis::Z:
            default:
                finalPos = basePos;
                finalColor = FVector4(0.f, 0.f, 1.f, .2f);
                break;
            }

            vertex.XYZ = finalPos;
            vertex.RGBA = finalColor;
            Vertices.push_back(vertex);
        }
    }

    for (int i = 0; i < majorSegments; ++i) {
        for (int j = 0; j < minorSegments; ++j) {
            int first = (i * (minorSegments + 1)) + j;
            int second = first + minorSegments + 1;
            int third = first + 1;
            int fourth = second + 1;

            Indices.push_back(first);
            Indices.push_back(second);
            Indices.push_back(third);

            Indices.push_back(third);
            Indices.push_back(second);
            Indices.push_back(fourth);
        }
    }

    FMeshData TorusData;
    TorusData.Indices = Indices;
    TorusData.Vertices = Vertices;
    return TorusData;
}