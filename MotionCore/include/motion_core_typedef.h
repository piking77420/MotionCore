#pragma once
#include <queue>
#include <variant>

#include "primitive/primitive.h"

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
            Sphere sphere;
            OBB obb;
            Caspule caspule;
            uint32_t physicsMeshId = -1;

            // for std vector  it's deleted function
            Body() {}
            ~Body() {};
        };
        Body data;
        uint32_t bodyId = NULLBODY;
        AABB worldAABB;
    };
    

    struct Body
    {
        Vec3 velocity;
        uint32_t id = NULLBODY;
        
        Vec3 lastFrameAcceleration;
        uint32_t primitiveIndex = NULLPRIMITVE;
        
        Vec3 angularVelocity;
        numeric invMass = static_cast<numeric>(1.f);
        
        Quat rotation;
        PhyscicalMaterial physcicalMaterial;
        
        bool isAwake = false;
        Vec3 forceAccumulation;
    
        Vec3 torqueAccumulation;
    };
    

    struct BodyCreateInfo
    {
        Vec3 position;
        numeric mass;
        
        Quat rotation;
        PrimitiveInfo bodyTypeInfo;
        PhyscicalMaterial physcicalMaterial; 
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


    struct ConvexHull
    {
        uint32_t id = -1;
        std::vector<Tbx::Vector3f> hullverticies;
    };

    struct MeshData
    {
        uint32_t id = -1;
        Vec3 worldCenterOfMass;
        ConvexHull convexHull;
    };
    
    struct MotionCoreContext
    {
        std::vector<Body> bodies;
        std::vector<PrimitiveInfo> primitiveInfo;
        std::queue<CollisionPoint> collisionPoint;
        std::vector<MeshData> meshDatas;
    };

    struct PhysicMaterial
    {
        numeric drag = static_cast<numeric>(0.99);
        numeric restitutionCoef = static_cast<numeric>(0.99);
    };

    inline const Vec3& GetPositionFromPrimitive(const PrimitiveInfo& _primitiveInfo)
    {
        switch (_primitiveInfo.bodyType)
        {
        case NONE:
            break;
        case SPHERE:
            return _primitiveInfo.data.sphere.center;
            break;
        case BOX:
            return _primitiveInfo.data.sphere.center;
            break;
        case CAPSULE:
            return _primitiveInfo.data.caspule.center;
            break;
        case MESH:
            // TODO 
                break;
        default: ;
        }    
    }

    inline Vec3& SetPositionFromPrimitive(PrimitiveInfo* _primitiveInfo)
    {
        switch (_primitiveInfo->bodyType)
        {
        case NONE:
            break;
        case SPHERE:
            return _primitiveInfo->data.sphere.center;
            break;
        case BOX:
            return _primitiveInfo->data.sphere.center;
            break;
        case CAPSULE:
            return _primitiveInfo->data.caspule.center;
            break;
        case MESH:
            // TODO 
                break;
        default: ;
        }    
    }

    inline AABB GetAABBFromOBB(const OBB& _obb)
    {
        AABB aabb;
    
        const Tbx::Matrix3x3<numeric> m = _obb.orientationMatrix;
        const Vec3& ext = _obb.extend;
        aabb.max = _obb.center;
        aabb.min = _obb.center;

        for (size_t i = 0; i < 3; i++)
        {
            const Vec3 axisScaled = Vec3(m[i][0], m[i][1], m[i][2]) * ext[i];

            for (size_t j = 0; j < 3; j++)
            {
                aabb.min[i] -= std::abs(axisScaled[j]);
                aabb.max[i] += std::abs(axisScaled[j]);
            }
        }

        return aabb;
    }
}
