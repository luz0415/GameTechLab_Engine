#include "CollisionManager.h"
#include "SceneManager.h" // To get the current scene
#include "PrimitiveComponent.h" // To access UPrimitiveComponent methods
#include <cfloat> // For FLT_MAX

UCollisionManager::UCollisionManager()
{
    // Constructor implementation
}

UCollisionManager::~UCollisionManager()
{
    // Destructor implementation
}

void UCollisionManager::CheckCollisions()
{
    UScene* CurrentScene = USceneManager::Get()->GetCurrentScene();
    if (!CurrentScene)
    {
        return;
    }

    // Example: Perform a raycast from a fixed point in a fixed direction
    // In a real application, this ray would come from a camera, mouse click, etc.
    FRay SampleRay(FVector(0.0f, 0.0f, -10.0f), FVector(0.0f, 0.0f, 1.0f)); // Ray pointing along +Z from -10Z

    UE_LOG("Performing sample raycast from Origin: (%.2f, %.2f, %.2f), Direction: (%.2f, %.2f, %.2f)",
           SampleRay.GetOrigin().X, SampleRay.GetOrigin().Y, SampleRay.GetOrigin().Z,
           SampleRay.GetDirection().X, SampleRay.GetDirection().Y, SampleRay.GetDirection().Z);

    float ClosestHitDistance = FLT_MAX;
    UPrimitiveComponent* HitComponent = nullptr;
    FHitRecord OutHit;

    // Iterate through all primitive components in the scene
    for (UPrimitiveComponent* Component : CurrentScene->Objects)
    {
        if (Component)
        {
            float CurrentHitDistance;
            FHitRecord CurrentOutHit;
            if (Component->Raycast(SampleRay, FLT_MAX, CurrentOutHit)) // TMax as FLT_MAX for now
            {
                if (CurrentOutHit.Time < ClosestHitDistance)
                {
                    ClosestHitDistance = CurrentOutHit.Time;
                    HitComponent = Component;
                    OutHit = CurrentOutHit;
                }
            }
        }
    }

    if (HitComponent)
    {
        UE_LOG("Raycast Hit! Component: %s, Hit Distance: %.2f, Hit Point: (%.2f, %.2f, %.2f)",
               HitComponent->GetClass()->GetClassName().c_str(), OutHit.Time,
               OutHit.Point.X, OutHit.Point.Y, OutHit.Point.Z);
    }
    else
    {
        UE_LOG("Raycast Missed all objects.");
    }
}

bool UCollisionManager::RayCast(const FRay& Ray, UPrimitiveComponent* Component, float& OutHitDistance)
{
    // This function will be implemented after UPrimitiveComponent is updated to expose mesh data.
    // For now, it's a placeholder.
    UE_LOG("UCollisionManager::RayCast() called. (Placeholder)");
    return false;
}

bool UCollisionManager::IntersectMeshTriangles(const FRay& Ray, const FMeshData& MeshData, float& OutHitDistance)
{
    OutHitDistance = FLT_MAX; // Initialize with a very large value

    // Iterate through all triangles in the mesh
    for (size_t i = 0; i < MeshData.Indices.size(); i += 3)
    {
        FVector V0 = MeshData.Vertices[MeshData.Indices[i]].XYZ;
        FVector V1 = MeshData.Vertices[MeshData.Indices[i+1]].XYZ;
        FVector V2 = MeshData.Vertices[MeshData.Indices[i+2]].XYZ;

        float CurrentHitDistance;
        if (RayTriangleIntersection(Ray, V0, V1, V2, CurrentHitDistance))
        {
            if (CurrentHitDistance < OutHitDistance)
            {
                OutHitDistance = CurrentHitDistance;
            }
        }
    }

    return OutHitDistance != FLT_MAX; // Return true if any intersection occurred
}
