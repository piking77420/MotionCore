#include "core/integrator.hpp"



void MotionCore::Integrator::IntegrateBodies(ObjectInfo* _objectInfo, const Vec3& _gravity, numeric _deltaTime)
{
    m_ObjectInfo = _objectInfo;
    std::vector<Body>& bodies = _objectInfo->bodies;
    deltatime = _deltaTime;

    for (Body& body : bodies)
    {
        if (body.id == NULLBODY || !body.isAwake)
            continue;
        
        //body.force += _gravity;
        ComputePosition(&body);
        ComputeRotation(&body);

        
        body.forceAccumulation = {};
        body.torqueAccumulation = {};
       
    }
}

void MotionCore::Integrator::ComputePosition(Body* body) const
{
    const Vec3 acceleration = body->forceAccumulation * body->invMass;
    body->lastFrameAcceleration = acceleration; 
    
    body->velocity += body->lastFrameAcceleration * deltatime;
    body->position += body->lastFrameAcceleration * static_cast<numeric>(0.5) * deltatime * deltatime + body->velocity * deltatime;
    const numeric dampingValue = pow(body->physcicalMaterial.damping, deltatime); 
    body->velocity *= dampingValue;
}

void MotionCore::Integrator::ComputeRotation(Body* body) const
{
    const Tbx::Matrix3x3<numeric> InverTensor = GetInvertInertiaTensor(*body);
        
    const Vec3 angularAcceleration = InverTensor * body->torqueAccumulation;
    body->angularVelocity += angularAcceleration * deltatime;
    body->rotation +=  body->angularVelocity * deltatime * static_cast<numeric>(0.5);
    body->rotation = body->rotation.Normalize();
    
    body->angularVelocity *= pow(body->physcicalMaterial.angularDamping, deltatime);
}


Tbx::Matrix3x3<MotionCore::numeric> MotionCore::Integrator::GetInvertInertiaTensor(const Body& body) const
{
    const PrimitiveInfo type = m_ObjectInfo->primitiveInfo[body.primitiveIndex];

    if (type.bodyType == NONE)
        return Tbx::Matrix3x3<MotionCore::numeric>::Identity();
    
    Tbx::Matrix3x3<numeric> tensor;
    constexpr numeric zero = static_cast<numeric>(0);
    constexpr numeric constantSphere = static_cast<numeric>(0.4);
    constexpr numeric constantBox = static_cast<numeric>(1) / static_cast<numeric>(12);
    const numeric mass = static_cast<numeric>(1) / body.invMass;

    
    switch (type.bodyType)
    {
    case NONE: // NOLINT(bugprone-branch-clone)
        break;
    case SPHERE:
        {
            const numeric radiusSquare = type.data.radius * type.data.radius;
            const numeric value = radiusSquare * mass * constantSphere;
        
            tensor =
            {
                {value, zero,zero},
                {zero,value,zero},
                {zero,zero,value}
            };
            break;
        }
    case BOX:
        {
            
            const Vec3 extend = (type.data.max - type.data.min) * static_cast<numeric>(0.5);
            const numeric PowerX = extend.x * extend.x;
            const numeric PowerY = extend.y * extend.y;
            const numeric PowerZ = extend.z * extend.z;

            tensor =
            {
                {constantBox * mass * (PowerY + PowerZ), zero, zero},
                {zero,constantBox * mass * (PowerX + PowerZ),zero},
                {zero,constantBox * mass * (PowerX + PowerY),zero}
            }; 
        }
        break;
    case CAPSULE:
        {
            
        }
        break;
    case MESH:
        {
            
        }
        break;
    default: ; // NOLINT(clang-diagnostic-covered-switch-default)
    }
    
    return Tbx::Invert(tensor);
}
