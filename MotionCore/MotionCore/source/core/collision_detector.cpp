#include "core/collision_detector.hpp"

void MotionCore::CollisionDetector::FoundCollision(MotionCoreContext* _objectInfo)
{
    motionCoreContext = _objectInfo;
    
    std::vector<Body>& bodies = _objectInfo->bodies;

    for (Body& body : bodies)
    {
        ComputeWorldABBB(&body);

    }
    
}

MotionCore::CollisionDetector::SphereCollisionInfo MotionCore::CollisionDetector::SphereCollision(
    numeric _sphereRadius1, numeric _sphereRadius2, const Vec3& _bodyPos1, const Vec3& _bodyPos2)
{
    const Vec3 sphereDirectionVector = _bodyPos2 - _bodyPos1;
    const numeric distanceSquare = sphereDirectionVector.MagnitudeSquare();
    const numeric radiusSum = _sphereRadius1 * _sphereRadius1 + _sphereRadius2 * _sphereRadius2;

    SphereCollisionInfo sphereCollisionInfo;
    if (distanceSquare < radiusSum)
        return {.normal = {}, .depth = {}, .hitResult = false};
    
    return {.normal = sphereDirectionVector.Normalize(), .depth = sqrtf(distanceSquare), .hitResult = true};
}

void MotionCore::CollisionDetector::ComputeWorldABBB(Body* body) const
{
    Tbx::Matrix3x3<numeric> matrix;
    Tbx::RotationMatrix3D(body->rotation, &matrix);

    
}

MotionCore::AABB MotionCore::CollisionDetector::GetLocalAABB(Body* _body) const
{
    PrimitiveInfo primitiveInfo = motionCoreContext->primitiveInfo.at(_body->primitiveIndex);
    AABB returnAabb;
    
    switch (primitiveInfo.bodyType)
    {
    case NONE:
        break;
    case SPHERE:
        returnAabb.extend = primitiveInfo.data.sphere.radius;
        break;
    case BOX:
        returnAabb = primitiveInfo.data.aabb;
        break;
    case CAPSULE:
        break;
    case MESH:
        break;
    default: ;
    }

    return returnAabb;
}
