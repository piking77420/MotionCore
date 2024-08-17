#pragma once

#include "motion_core_header.h"
#include "motion_core_typedef.h"

namespace MotionCore
{
    
    class Integrator
    {
    public:
        Integrator() = default;

        ~Integrator() = default;

        FORCEINLINE void AddForce(Body* _body, const Vec3& _force)
        {
            _body->forceAccumulation += _force;
            _body->isAwake = true;
        }

        FORCEINLINE void AddImpulse(Body* _body, const Vec3& _impulse)
        {
            _body->velocity += _impulse * _body->invMass;
            _body->isAwake = true;
        }

        FORCEINLINE void AddTorque(Body* _body, const Vec3& _torque)
        {
            _body->torqueAccumulation += _torque;
            _body->isAwake = true;
        }

        void IntegrateBodies(ObjectInfo* _objectInfo, const Vec3& _gravity, numeric _deltaTime);
    private:
        numeric deltatime = static_cast<numeric>(0);

        ObjectInfo* m_ObjectInfo = nullptr;
        
        void ComputePosition(Body* body) const;

        void ComputeRotation(Body* body) const;
        
        Tbx::Matrix3x3<numeric> GetInvertInertiaTensor(const Body& body) const;
    };
    
}
