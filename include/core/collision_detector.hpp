#pragma once

#include "motion_core_header.h"
#include "motion_core_typedef.h"
#include "spatial_partitioning/bonding_volume_hierarchyAABB.h"

namespace MotionCore
{
    class CollisionDetector
    {
    public:

        CollisionDetector() = default;

        ~CollisionDetector() = default;
        
        void FoundCollision(MotionCoreContext* _objectInfo);
    private:

        MotionCoreContext* motionCoreContext = nullptr;
        
        void ComputeWorldABBB(PrimitiveInfo* _primitiveInfo) const;

        MotionCore::AABB GetLocalAABB(const PrimitiveInfo& _primitiveInfoy) const;

        void BroadPhase();

        //BoundingVolumeHierarchyAABB bvh;

        std::vector<ObjectWithBoundingVolume> bvhObjects;
    };
}

