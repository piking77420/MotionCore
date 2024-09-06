#include "primitive/axis_aligned_bounding_box.h"

void MotionCore::AABB::GrowToInclude(const AABB& _other)
{
    for (size_t i = 0; i < 3; i++)
    {
        min[i] = std::min(min[i],_other.min[i]);
        max[i] = std::max(max[i],_other.max[i]);
    }
}

MotionCore::numeric MotionCore::AABB::GetGrowVolume(const AABB& _other) const 
{
    AABB copy = *this;
    copy.GrowToInclude(_other);
    return copy.GetArea();
}

bool MotionCore::AABB::Overlaps(const AABB& _other) const
{
    bool overlap = min.x > max.x;
    if(overlap) return false;
    
    overlap = min.y > max.y;
    if(overlap) return false;
    
    overlap = min.z > max.z;
    if(overlap) return false;
    
    overlap = max.x < min.x;
    if(overlap) return false;

    overlap = max.y < min.y;
    if(overlap) return false;
    
    overlap = max.z < min.z;
    if(overlap) return false;
    
    return true;
}

MotionCore::numeric MotionCore::AABB::GetArea() const
{
    const Vec3 size = max - min;
    return size.x * size.y * size.z;
}
