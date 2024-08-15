#pragma once

#include "motion_core_typedef.h"
#include "core/motion_core_allocator.h"
#include <queue>

#include "collision_solver.h"

namespace MotionCore
{
    struct PhyscicsEngineInitilizationParameters
    {
        numeric timeStep = static_cast<numeric>(0);
    };

    class PhysicsEngine
    {
    public:
       
        MOTION_CORE void Initialize(const PhyscicsEngineInitilizationParameters* _physcicsEngineInitilizationParameters);

        MOTION_CORE void Destroy();

        MOTION_CORE void Update(numeric _deltaTime);

        MOTION_CORE void AddForce(uint32_t _id, const Vec3& _forces);

        MOTION_CORE void AddImpulse(uint32_t _id, const Vec3& _impluse);

        MOTION_CORE uint32_t CreateBody(const CreateBodyInfo* _CreateBodyInfo);

    private:
        Tbx::Vector3f m_Gravity = {0.f, -9.81f, 0.f};
        
        struct TimeInfo
        {
            numeric accumulateTime = static_cast<numeric>(0);
            numeric timeStep = static_cast<numeric>(0);
        };

        TimeInfo timeInfo;

        ObjectInfo m_ObjectInfo;

        CollisionSolver m_CollisionSolver; 
        
        void Step(numeric _deltatime);

        void Integrate(numeric _deltatime);

        static inline void AddForce(Body* _body, Tbx::Vector3f _force)
        {
            _body->force += _force;
        }

        static inline void AddImpulse(Body* _body, Tbx::Vector3f _impulse)
        {
            _body->velocity += _impulse * _body->invMass;
        }
    };
}
