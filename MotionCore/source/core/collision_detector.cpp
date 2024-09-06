#include "core/collision_detector.hpp"


void MotionCore::CollisionDetector::FoundCollision(MotionCoreContext* _objectInfo)
{
    motionCoreContext = _objectInfo;
    std::vector<PrimitiveInfo>& primitive = _objectInfo->primitiveInfo;
    bvhObjects.resize(primitive.size());

    for (size_t i = 0; i < primitive.size(); i++)
    {
        if (primitive.at(i).bodyId == NULLBODY)
            continue;
        
        ComputeWorldABBB(&primitive.at(i));
        
        bvhObjects.at(i).objectPtr = &bvhObjects.at(i);
        bvhObjects.at(i).boundingAABB = {primitive.at(i).worldAABB.min, primitive.at(i).worldAABB.max};
        
    }

    //bvh.Clear();
    for (size_t i = 0; i < bvhObjects.size(); i++)
    {
       // bvh.Insert(&bvhObjects.at(i));
    }
    
    BroadPhase();
}


void MotionCore::CollisionDetector::ComputeWorldABBB(PrimitiveInfo* _primitiveInfo) const
{
    _primitiveInfo->worldAABB = GetLocalAABB(*_primitiveInfo);
}

MotionCore::AABB MotionCore::CollisionDetector::GetLocalAABB(const PrimitiveInfo& _primitiveInfo) const
{
    AABB returnAabb;
    
    switch (_primitiveInfo.bodyType)
    {
    case NONE:
        break;
    case SPHERE:
        returnAabb.max =  _primitiveInfo.data.sphere.center + _primitiveInfo.data.sphere.radius * static_cast<numeric>(0.5);
        returnAabb.min = _primitiveInfo.data.sphere.center - _primitiveInfo.data.sphere.radius * static_cast<numeric>(0.5);
        break;
    case BOX:
        returnAabb = GetAABBFromOBB(_primitiveInfo.data.obb);
        break;
    case CAPSULE:
        break;
    case MESH:
        break;
    default: ;
    }

    return returnAabb;
}

void MotionCore::CollisionDetector::BroadPhase()
{
    std::vector<Body>& bodies = motionCoreContext->bodies;

}

