#pragma once

#include "Core.h"
#include "Scene.h"
#include "Collision.h"
#include "MeshManager.h"

class UCollisionManager
{
private:
    UCollisionManager();
    ~UCollisionManager();
    UCollisionManager(const UCollisionManager&) = delete;
    UCollisionManager& operator=(const UCollisionManager&) = delete;

public:
    static UCollisionManager* Get()
    {
        static UCollisionManager Instance;
        return &Instance;
    }

    // Function to check for collisions between objects in the current scene
    void CheckCollisions();

    // Function to perform a ray-cast against a specific primitive component
    bool RayCast(const FRay& Ray, UPrimitiveComponent* Component, float& OutHitDistance);

private:
    // Helper function to perform triangle-level intersection for a mesh component
    bool IntersectMeshTriangles(const FRay& Ray, const FMeshData& MeshData, float& OutHitDistance);
};
