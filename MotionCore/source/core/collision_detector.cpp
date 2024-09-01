#include "core/collision_detector.hpp"

void MotionCore::CollisionDetector::FoundCollision(MotionCoreContext* _objectInfo)
{
    motionCoreContext = _objectInfo;
    std::vector<Body>& bodies = _objectInfo->bodies;

    for (Body& body : bodies)
    {
        if (body.id == NULLBODY || !body.isAwake)
            continue;
        ComputeWorldABBB(&body);
    }
    
}


void MotionCore::CollisionDetector::ComputeWorldABBB(Body* body) const
{
    body->worldAABB = GetLocalAABB(body);
    body->worldAABB = GetRotatedAABB(body->worldAABB, body->rotation);
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
        returnAabb.max = primitiveInfo.data.sphere.radius * static_cast<numeric>(0.5);
        returnAabb.min = -returnAabb.max;
        break;
    case BOX:
        returnAabb = GetAABBFromOBB(primitiveInfo.data.obb);
        break;
    case CAPSULE:
        break;
    case MESH:
        break;
    default: ;
    }

    return returnAabb;
}

