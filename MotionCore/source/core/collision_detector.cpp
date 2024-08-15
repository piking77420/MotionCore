#include "core/collision_detector.hpp"

void MotionCore::CollisionDetector::FoundCollision(ObjectInfo* objectInfo)
{
    /*
    std::vector<Body>& bodies = objectInfo->bodies;
    
    for (size_t i = 0; i < objectInfo->bodies.size(); ++i)
    {
        Body& b1 = m_Instance->particles[i];

        for (size_t j = i + 1; j < m_Instance->particles.size(); ++j)
        {
            Particule& p2 = m_Instance->particles[j];

            const float maxRadius = p1.radius + p2.radius; 
            Tbx::Vector2f vec = p2.body.position - p1.body.position;
            const float distanceSquare = vec.MagnitudeSquare(); 

            if (distanceSquare > maxRadius * maxRadius)
                continue;

            float depth = distanceSquare - maxRadius;

            CollisionPoint coll =
            {
                .b1 = &p1.body,
                .b2 = &p2.body,
                .normal = vec,
                .depth = depth, 
                .penetrationb1 = (p1.body.invMass + p2.body.invMass) / p2.body.invMass * depth,
                .penetrationb2 = -(p1.body.invMass + p2.body.invMass) / p1.body.invMass * depth

            };

            m_Instance->collisionPoint.push(coll);
        }
    }
    */
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
