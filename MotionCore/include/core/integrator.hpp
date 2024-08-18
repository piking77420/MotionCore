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

        void IntegrateBodies(MotionCoreContext* _objectInfo, const Vec3& _gravity, numeric _deltaTime);

        void SleepBodies(MotionCoreContext* _objectInfo);
    private:
        numeric deltatime = static_cast<numeric>(0);

        MotionCoreContext* m_ObjectInfo = nullptr;
        
        void ComputePosition(Body* body,PrimitiveInfo* _primitiveInfo) const;

        void ComputeRotation(Body* body, const PrimitiveInfo& _primitiveInfo) const;
        
        Tbx::Matrix3x3<numeric> GetInvertInertiaTensor(const Body& body, const PrimitiveInfo& _primitiveInfo) const;
    };
    
}
