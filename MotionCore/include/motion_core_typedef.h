
#pragma once
#include <queue>

#include "physic_material.h"

namespace MotionCore
{
    constexpr uint32_t NULLBODY = -1;
    
    struct CreateBodyInfo 
    {
        numeric mass = static_cast<numeric>(1.f);
    };
    
    struct PhyscicalMaterial
    {
        numeric drag = static_cast<numeric>(0.99);
    };
   

    enum BodyType
    {
        NONE,
        SPHERE,
        BOX,
        CAPSULE,
        MESH
    };
    
    struct Body
    {
        Vec3 position;
        uint32_t id = NULLBODY;
        
        Vec3 velocity;
        BodyType bodyType;
        
        Vec3 acceleration;
        numeric invMass = static_cast<numeric>(1.f);

        Tbx::Vector3f force;
        PhyscicalMaterial physcicalMaterial;
    };

    struct PrimitiveCreateInfo
    {
        BodyType bodyType;
        union body
        {
            numeric radius;
            numeric height;
            Vec3 min,max;
        };
    };
    
    struct BodyCreateInfo
    {
        Vec3 position;
        PrimitiveCreateInfo primitiveCreateInfo;
    };
    
    struct Sphere
    {
        uint32_t bodyId = NULLBODY;
        numeric radius = static_cast<numeric>(0.5);
    };

    struct BoundingBox
    {
        Vec3 min = Vec3(static_cast<numeric>(-0.5));
        Vec3 max = Vec3(static_cast<numeric>(0.5));
    };
    
    struct CollisionPoint
    {
        uint32_t bodyId1 = NULLBODY;
        uint32_t bodyId2 = NULLBODY;
        Tbx::Vector2f normal;

        float depth = 1.0f;
        float penetrationb1 = 0.0f;
        float penetrationb2 = 0.0f;
    };

    
    struct ObjectInfo
    {
        std::vector<Body> bodies;
        std::vector<Sphere> sphere;
        std::queue<CollisionPoint> collisionPoint;
    };

    struct PenetrationInfo
    {
        numeric penetrationB1;
    };
}

