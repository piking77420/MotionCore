#pragma once
#include <queue>
#include <variant>

#include "physic_material.h"

namespace MotionCore
{
    constexpr uint32_t NULLBODY = -1;
    constexpr uint32_t NULLPRIMITVE = -1;
    constexpr uint32_t MAX_BODIES = 100;
    
    struct PhyscicalMaterial
    {
        numeric damping = static_cast<numeric>(0.99);
        numeric angularDamping = static_cast<numeric>(0.99);
        numeric restitutionCoeff = static_cast<numeric>(1);
    };


    enum PrimitiveType
    {
        NONE,
        SPHERE,
        BOX,
        CAPSULE,
        MESH
    };

    struct PrimitiveInfo
    {
        PrimitiveType bodyType;
        
        union Body
        {
            numeric radius;
            numeric height;
            Vec3 min;
            Vec3 max;

            // for std vector else it's deleted function
            Body() {}
            ~Body() {};
        };
        Body data;
    };
    

    struct Body
    {
        Vec3 position;
        uint32_t id = NULLBODY;
        
        Vec3 velocity;
        uint32_t primitiveIndex = NULLPRIMITVE;
        
        Vec3 worldCenterOfMass;
        numeric invMass = static_cast<numeric>(1.f);

        Vec3 lastFrameAcceleration;
        
        Quat rotation;
        PhyscicalMaterial physcicalMaterial;

        Vec3 angularVelocity;
        bool isAwake = false;
        
        Vec3 torqueAccumulation;
        Vec3 forceAccumulation;
    };
    

    struct BodyCreateInfo
    {
        Vec3 position;
        numeric mass;
        
        Quat rotation;
        PrimitiveInfo bodyTypeInfo;
        PhyscicalMaterial physcicalMaterial; 
    };
    
    struct Sphere
    {
        uint32_t bodyId = NULLBODY;
        numeric radius = static_cast<numeric>(0.5);
    };

    struct BoundingBox
    {
        uint32_t bodyId = NULLBODY;
        Vec3 min = Vec3(static_cast<numeric>(-0.5));
        Vec3 max = Vec3(static_cast<numeric>(0.5));
    };

    struct PenetrationInfo
    {
        numeric penetrationB1;
        numeric penetrationB2;
    };

    struct CollisionPoint
    {
        uint32_t bodyId1 = NULLBODY;
        uint32_t bodyId2 = NULLBODY;
        Tbx::Vector3f normal;

        numeric depth = 1.0f;
        PenetrationInfo penetrationInfo;
    };


    struct ObjectInfo
    {
        std::vector<Body> bodies;
        std::vector<PrimitiveInfo> primitiveInfo;
        std::queue<CollisionPoint> collisionPoint;
    };
}
